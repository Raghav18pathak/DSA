class Solution {
public:
    bool isPalindrome(string s) {
        string a;
        for(int i = 0 ; i < s.size() ; i++){
            if(isalnum(s[i]))a.push_back(tolower(s[i]));
        }
        string temp = a;
        for(int i = 0 ; i<temp.size()/2;i++){
            swap(temp[i],temp[temp.size()-1-i]);
        }
        if(temp == a)return true;
        else return false;
    }
};