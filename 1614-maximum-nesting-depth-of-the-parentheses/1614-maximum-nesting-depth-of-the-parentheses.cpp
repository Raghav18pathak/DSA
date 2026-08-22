class Solution {
public:
    int maxDepth(string s) {
        int maxu = 0;
        int balance = 0 ;
        for(int i = 0 ; i < s.size() ; i++){
            if(s[i]=='('){
                balance++;
                maxu = max(maxu,balance);
            }
            else if(s[i]==')') balance--;
            else continue;
        }
        return maxu;
    }
};