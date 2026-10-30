#!/usr/bin/env node
/**
 * organize-dsa.mjs
 *
 * Reorganizes an existing DSA repo (LeetHub-style numbered folders, GFG folders named
 * by title, "Difficulty: X/" folders, loose files) into the layout the modified
 * CommitDSA extension writes:
 *
 *   <Basic|Easy|Medium|Hard>/<LC|GFG>-<number>-<Title-Slug>/solution.<ext>
 *   <Basic|Easy|Medium|Hard>/<LC|GFG>-<number>-<Title-Slug>/README.md
 *
 * It also rebuilds the root README with a DSA-TABLE-START/END table in the exact
 * format the extension reads and updates.
 *
 * Usage (run from the ROOT of your DSA repo, on Linux/macOS/Codespaces):
 *   node organize-dsa.mjs            -> DRY RUN: prints the plan, changes nothing
 *   node organize-dsa.mjs --apply    -> performs the moves with `git mv`
 *
 * Folder naming below intentionally copies the extension's own functions
 * (src/utils/path.js) so that re-solving a problem later updates the same folder.
 */

import fs from 'node:fs';
import path from 'node:path';
import { execFileSync } from 'node:child_process';

const APPLY = process.argv.includes('--apply');
const ROOT = process.cwd();

/* ------------------------------------------------------------------ */
/* MANUAL OVERRIDES: fill in any folder the script could not classify. */
/* Key = old folder path (exactly as printed by the dry run).          */
/* Example:                                                            */
/*   'Floor and Ciel': { platform: 'gfg', difficulty: 'Easy',          */
/*                       title: 'Floor in a Sorted Array',             */
/*                       slug: 'floor-in-a-sorted-array',              */
/*                       url: 'https://...' },                         */
/* ------------------------------------------------------------------ */
const MANUAL = {
  // These 5 are Naukri Code360 (Coding Ninjas) problems: not LeetCode/GFG, so the
  // extension has no platform for them. They go to Code360/<Title>/ (no difficulty folder).
  // Edit `difficulty` below if you want it shown in the README table ('' shows a dash).
  'Floor and Ciel':            { folder: 'Code360', platformLabel: 'Code360', title: 'Ceil The Floor',              url: 'https://www.naukri.com/code360/problems/ceil-the-floor_630291',                difficulty: '' },
  'Implement Lower Bound':     { folder: 'Code360', platformLabel: 'Code360', title: 'Implement Lower Bound',       url: 'https://www.naukri.com/code360/problems/lower-bound_816511',                   difficulty: '' },
  'Implement Upper Bound':     { folder: 'Code360', platformLabel: 'Code360', title: 'Implement Upper Bound',       url: 'https://www.naukri.com/code360/problems/implement-upper-bound_816538',         difficulty: '' },
  'LONGEST SUBARRAY POSITIVE': { folder: 'Code360', platformLabel: 'Code360', title: 'Longest Subarray With Sum K', url: 'https://www.naukri.com/code360/problems/longest-subarray-with-sum-k_6682399', difficulty: '' },
  'UNION OF TWO ARRAYS':       { folder: 'Code360', platformLabel: 'Code360', title: 'Union of Two Sorted Arrays',  url: 'https://www.naukri.com/code360/problems/sorted-array_6613259',                 difficulty: '' },
};

/* ------------------------------------------------------------------ */
/* Copies of the extension's helpers (src/utils/path.js)               */
/* ------------------------------------------------------------------ */
function getFolderCategory(platform, difficulty) {
  if (!difficulty) return 'Medium';
  const d = difficulty.trim().toLowerCase();
  const p = platform.toLowerCase();
  if (p === 'leetcode') {
    if (d.includes('easy')) return 'Easy';
    if (d.includes('hard')) return 'Hard';
    return 'Medium';
  }
  if (p === 'gfg') {
    if (d.includes('school') || d.includes('basic')) return 'Basic';
    if (d.includes('easy')) return 'Easy';
    if (d.includes('hard')) return 'Hard';
    return 'Medium';
  }
  return 'Medium';
}

function getProblemFolderSlug(title) {
  const withoutNumber = (title || '').trim().replace(/^\d+[\.\s]+/, '');
  const slug = withoutNumber
    .replace(/[^a-zA-Z0-9\s-]/g, '')
    .trim()
    .replace(/[\s-]+/g, '-');
  return slug || 'Problem';
}

function getProblemNumber(title, slug = '') {
  const source = `${title || ''} ${slug || ''}`;
  const match = source.match(/(?:^|\D)(\d{1,})/);
  return String(match ? parseInt(match[1], 10) : 0).padStart(4, '0');
}

/* ------------------------------------------------------------------ */
/* Helpers                                                             */
/* ------------------------------------------------------------------ */
const CODE_EXTS = new Set(['cpp', 'c', 'py', 'java', 'js', 'ts', 'cs', 'go', 'rs', 'kt', 'rb', 'swift', 'php', 'sql', 'scala']);
const SKIP_TOP = new Set(['.git', '.github', 'node_modules', 'LICENSE', 'README.md', 'stats.json', '.gitignore']);
const CATEGORIES = new Set(['Basic', 'Easy', 'Medium', 'Hard']);

const git = (...args) => execFileSync('git', args, { cwd: ROOT, stdio: ['ignore', 'pipe', 'pipe'] }).toString();
const ext = f => path.extname(f).slice(1).toLowerCase();
const read = p => fs.readFileSync(p, 'utf8');
const rel = p => path.relative(ROOT, p).split(path.sep).join('/');

function readStatsDifficulties() {
  const out = {};
  try {
    const stats = JSON.parse(read(path.join(ROOT, 'stats.json')));
    for (const [folder, v] of Object.entries(stats?.leetcode?.shas || {})) {
      if (v && typeof v === 'object' && v.difficulty) out[folder] = v.difficulty;
    }
  } catch { /* stats.json optional */ }
  return out;
}

/** Recursively find "problem folders": folders directly containing a code file. */
function findProblemFolders(dir, found = []) {
  for (const entry of fs.readdirSync(dir, { withFileTypes: true })) {
    if (SKIP_TOP.has(entry.name) && dir === ROOT) continue;
    if (entry.name.startsWith('.')) continue;
    const full = path.join(dir, entry.name);
    if (entry.isDirectory()) {
      findProblemFolders(full, found);
    }
  }
  const files = fs.readdirSync(dir, { withFileTypes: true }).filter(e => e.isFile());
  const codeFiles = files.filter(f => CODE_EXTS.has(ext(f.name)));
  if (dir !== ROOT && codeFiles.length) found.push({ dir, codeFiles: codeFiles.map(f => f.name), hasReadme: files.some(f => f.name === 'README.md') });
  return found;
}

function alreadyOrganized(dir) {
  const r = rel(dir);
  const parts = r.split('/');
  return parts.length === 2 && CATEGORIES.has(parts[0]) && /^(LC|GFG)-/.test(parts[1]);
}

function titleCase(slug) {
  return slug.split('-').filter(Boolean).map(w => w[0].toUpperCase() + w.slice(1)).join(' ');
}

function inferFromHeader(codeText) {
  const link = codeText.match(/Problem Link\s*:\s*(\S+)/i)?.[1];
  const diff = codeText.match(/Difficulty\s*:\s*([A-Za-z]+)/i)?.[1];
  return { link, diff };
}

function platformFromUrl(url = '') {
  if (/leetcode\.com/i.test(url)) return 'leetcode';
  if (/geeksforgeeks\.org/i.test(url)) return 'gfg';
  return null;
}

function slugFromUrl(url, platform) {
  if (!url) return '';
  const m = url.match(/\/problems\/([^/?#]+)/);
  return m ? m[1] : '';
}

function canonicalUrl(platform, slug) {
  return platform === 'leetcode'
    ? `https://leetcode.com/problems/${slug}/`
    : `https://practice.geeksforgeeks.org/problems/${slug}/1`; // same shape the extension stores
}

/* ------------------------------------------------------------------ */
/* Classify every problem folder                                       */
/* ------------------------------------------------------------------ */
const statsDiff = readStatsDifficulties();
const items = [];
const unresolved = [];
const notes = [];

for (const pf of findProblemFolders(ROOT)) {
  if (alreadyOrganized(pf.dir)) continue;
  const oldDir = rel(pf.dir);
  const folderName = path.basename(pf.dir);
  const parentName = path.basename(path.dirname(pf.dir));

  if (pf.codeFiles.length > 1) {
    notes.push(`${oldDir}: has ${pf.codeFiles.length} code files (${pf.codeFiles.join(', ')}). Only the first is moved as solution; handle the rest by hand.`);
  }
  const codeFile = pf.codeFiles[0];
  const codeText = read(path.join(pf.dir, codeFile));

  let platform = null, title = '', url = '', difficulty = '';

  if (pf.hasReadme) {
    const readme = read(path.join(pf.dir, 'README.md'));
    const h = readme.match(/<h2><a href="([^"]+)">([\s\S]*?)<\/a><\/h2>/);
    if (h) {
      url = h[1];
      title = h[2].replace(/<[^>]+>/g, '').replace(/&amp;/g, '&').replace(/&#39;/g, "'").replace(/&quot;/g, '"').trim();
      platform = platformFromUrl(url);
    }
    const lc = readme.match(/<h3>\s*(Easy|Medium|Hard)\s*<\/h3>/i);
    const gfg = readme.match(/Difficulty:\s*(School|Basic|Easy|Medium|Hard)/i);
    difficulty = (platform === 'gfg' ? gfg?.[1] : lc?.[1]) || lc?.[1] || gfg?.[1] || '';
  }

  const header = inferFromHeader(codeText);
  if (!url && header.link) { url = header.link; platform = platformFromUrl(url); }
  if (!difficulty && header.diff) difficulty = header.diff;
  if (!difficulty && statsDiff[folderName]) difficulty = statsDiff[folderName];
  if (!difficulty) {
    const pm = parentName.match(/(Easy|Medium|Hard|Basic|School)/i);
    if (pm) difficulty = pm[1];
  }
  if (!platform && /^leetcode$/i.test(path.basename(path.dirname(path.dirname(pf.dir))))) platform = 'leetcode';

  let slug = slugFromUrl(url, platform);
  if (!title && slug) {
    // Loose files like 5_LongestPalindromicSubstring.cpp: take the number from the filename
    const num = codeFile.match(/^(\d+)_/)?.[1];
    title = (num ? `${parseInt(num, 10)}. ` : '') + titleCase(slug);
  }

  // LeetHub sometimes wrote LeetCode's internal id into the README title (e.g. "792. Binary Search"
  // for problem 704). The folder prefix (0704-...) is the real problem number, so trust that.
  if (platform === 'leetcode') {
    const folderNum = folderName.match(/^(\d+)-/)?.[1];
    if (folderNum && title) title = `${parseInt(folderNum, 10)}. ${title.replace(/^\d+\.\s*/, '')}`;
  }

  const manual = MANUAL[oldDir];
  if (manual?.folder) {
    // Other platforms (e.g. Code360): own top-level folder, no difficulty subfolder
    const newDir = `${manual.folder}/${getProblemFolderSlug(manual.title)}`;
    items.push({
      oldDir, codeFile, hasReadme: pf.hasReadme, platform: 'other', platformLabel: manual.platformLabel,
      title: manual.title, slug: '', category: manual.folder, difficulty: manual.difficulty || '',
      url: manual.url, newDir, newCode: `${newDir}/solution.${ext(codeFile)}`
    });
    continue;
  }
  if (manual) {
    platform = manual.platform ?? platform;
    difficulty = manual.difficulty ?? difficulty;
    title = manual.title ?? title;
    slug = manual.slug ?? slug;
    url = manual.url ?? url;
  }

  if (!platform || !difficulty || !title || !slug) {
    unresolved.push({ oldDir, codeFile, found: { platform, difficulty, title, slug } });
    continue;
  }

  const prefix = platform === 'leetcode' ? 'LC' : 'GFG';
  const category = getFolderCategory(platform, difficulty);
  const newDir = `${category}/${prefix}-${getProblemNumber(title, slug)}-${getProblemFolderSlug(title)}`;
  items.push({
    oldDir, codeFile, hasReadme: pf.hasReadme, platform, title, slug, category, difficulty,
    url: canonicalUrl(platform, slug),
    newDir,
    newCode: `${newDir}/solution.${ext(codeFile)}`
  });
}

/* Destination collisions */
const seen = new Map();
for (const it of items) {
  if (seen.has(it.newCode)) notes.push(`COLLISION: ${it.oldDir} and ${seen.get(it.newCode)} both map to ${it.newCode}. Resolve by hand.`);
  else seen.set(it.newCode, it.oldDir);
  if (fs.existsSync(path.join(ROOT, it.newCode))) notes.push(`COLLISION: ${it.newCode} already exists on disk.`);
}

/* ------------------------------------------------------------------ */
/* Report                                                              */
/* ------------------------------------------------------------------ */
console.log(`\n${APPLY ? 'APPLYING' : 'DRY RUN'}: ${items.length} problems classified, ${unresolved.length} need a decision.\n`);
const order = ['Basic', 'Easy', 'Medium', 'Hard', 'Code360'];
items.sort((a, b) => order.indexOf(a.category) - order.indexOf(b.category) || a.platform.localeCompare(b.platform) || a.newDir.localeCompare(b.newDir));
for (const it of items) console.log(`${it.category.padEnd(7)} ${it.platform === 'leetcode' ? 'LC ' : it.platform === 'gfg' ? 'GFG' : 'OTH'}  ${it.oldDir}  ->  ${it.newDir}/`);

if (unresolved.length) {
  console.log('\nNEED A DECISION (add each to MANUAL at the top of this script, then re-run):');
  for (const u of unresolved) console.log(`  - "${u.oldDir}"  (file: ${u.codeFile})  found so far: ${JSON.stringify(u.found)}`);
}
if (notes.length) { console.log('\nNOTES:'); notes.forEach(n => console.log('  - ' + n)); }

const counts = { Basic: 0, Easy: 0, Medium: 0, Hard: 0, Code360: 0 };
items.forEach(i => counts[i.category]++);
console.log(`\nCounts -> Basic: ${counts.Basic}, Easy: ${counts.Easy}, Medium: ${counts.Medium}, Hard: ${counts.Hard}, Code360: ${counts.Code360}`);

if (!APPLY) {
  console.log('\nNothing was changed. Review the list, fill in MANUAL if needed, then run with --apply.');
  process.exit(0);
}
if (unresolved.length || notes.some(n => n.startsWith('COLLISION'))) {
  console.error('\nRefusing to apply while problems are unresolved or colliding. Fix them first.');
  process.exit(1);
}

/* ------------------------------------------------------------------ */
/* Apply: git mv                                                       */
/* ------------------------------------------------------------------ */
for (const it of items) {
  fs.mkdirSync(path.join(ROOT, it.newDir), { recursive: true });
  git('mv', `${it.oldDir}/${it.codeFile}`, it.newCode);
  if (it.hasReadme) {
    git('mv', `${it.oldDir}/README.md`, `${it.newDir}/README.md`);
  } else {
    const md = `# ${it.title}\n\n- **Platform:** ${it.platform === 'leetcode' ? 'LeetCode' : it.platform === 'gfg' ? 'GeeksforGeeks' : it.platformLabel}\n- **Difficulty:** ${it.platform === 'other' ? (it.difficulty || '-') : it.category}\n- **Problem:** [${it.url}](${it.url})\n- **Solution:** [solution.${ext(it.codeFile)}](./solution.${ext(it.codeFile)})\n`;
    fs.writeFileSync(path.join(ROOT, it.newDir, 'README.md'), md);
    git('add', `${it.newDir}/README.md`);
  }
}

/* Remove emptied old folders (walk upward) */
function pruneEmpty(dir) {
  if (dir === ROOT || !fs.existsSync(dir)) return;
  if (fs.readdirSync(dir).length === 0) {
    fs.rmdirSync(dir);
    pruneEmpty(path.dirname(dir));
  }
}
for (const it of items) pruneEmpty(path.join(ROOT, it.oldDir));

/* ------------------------------------------------------------------ */
/* Rebuild the root README with the extension's table format           */
/* ------------------------------------------------------------------ */
const START = '<!-- DSA-TABLE-START -->';
const END = '<!-- DSA-TABLE-END -->';
const platformLabel = r => (r.platform === 'leetcode' ? 'LeetCode' : r.platform === 'gfg' ? 'GeeksforGeeks' : r.platformLabel);
const rows = [...items];
const c2 = { Easy: 0, Medium: 0, Hard: 0, Basic: 0 };
rows.forEach(r => { if (c2[r.category] !== undefined) c2[r.category]++; });

let table = `${START}\nSummary: ${rows.length} solved (Easy: ${c2.Easy}, Medium: ${c2.Medium}, Hard: ${c2.Hard}, Basic: ${c2.Basic})\n\n`;
table += '| # | Problem | Platform | Difficulty | Solution |\n| --- | --- | --- | --- | --- |\n';
rows.forEach((r, i) => {
  table += `| ${i + 1} | [${r.title.replace(/\|/g, '\\|')}](${r.url}) | ${platformLabel(r)} | ${r.platform === 'other' ? (r.difficulty || '-') : r.category} | [Solution](./${r.newCode}) |\n`;
});
table += END;

const readmePath = path.join(ROOT, 'README.md');
let readme = fs.existsSync(readmePath) ? read(readmePath) : '# DSA\n';
// Remove old LeetHub topics block and the older Web Store block (if present)
readme = readme.replace(/<!---LeetCode Topics Start-->[\s\S]*?<!---LeetCode Topics End-->\s*/g, '');
readme = readme.replace(/<!-- COMMITDSA_START -->[\s\S]*?<!-- COMMITDSA_END -->\s*/g, '');
readme = readme.replace(new RegExp(`${START}[\\s\\S]*?${END}\\s*`, 'g'), '');
readme = readme.trimEnd() + '\n\n' + table + '\n';
fs.writeFileSync(readmePath, readme);
git('add', 'README.md');

console.log('\nDone. Review with `git status`, then commit and push:');
console.log('  git commit -m "Reorganize solutions by difficulty"');
console.log('  git push');
console.log('Note: stats.json is left untouched (it belongs to the old LeetHub extension).');
