# [Union of Two Sorted Arrays](https://www.naukri.com/code360/problems/sorted-array_6613259)

## Problem Statement
Given two sorted arrays, `a` and `b`, of size `n` and `m` respectively, return the **union** of the arrays.
The union of two sorted arrays can be defined as an array consisting of the common and the distinct elements of the two arrays. The final array should be sorted in ascending order.

**Note:** `a` and `b` may contain duplicate elements, but the union array must contain **unique** elements.

---

## Example 1:
**Input:** `n = 5, m = 3`
`a = [1, 2, 3, 4, 6]`
`b = [2, 3, 5]`

**Output:** `[1, 2, 3, 4, 5, 6]`

**Explanation:** Common elements: `[2, 3]`
Distinct elements: `[1, 4, 5, 6]`
Union: `[1, 2, 3, 4, 5, 6]`

---

## Complexity Analysis
- **Time Complexity:** $O(n + m)$  
  We traverse both arrays exactly once using the two-pointer approach.
- **Space Complexity:** $O(n + m)$  
  In the worst case (all elements are distinct), the result vector will store $n + m$ elements.

---

## Constraints:
- $1 \le n, m \le 10^5$
- $-10^9 \le a[i], b[j] \le 10^9$
- Arrays `a` and `b` are sorted in non-decreasing order.
- Time Limit: 1 sec
