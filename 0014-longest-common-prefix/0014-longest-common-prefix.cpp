class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ans;
        sort(strs.begin(),strs.end());
        string first = strs[0];
        string last = strs[strs.size()-1];
        int length = min(first.size(),last.size());
        for(int i = 0 ; i < length ; i++){
            if(first[i]==last[i]) ans+=first[i];
            else break;
        }
        return ans;
    }
};