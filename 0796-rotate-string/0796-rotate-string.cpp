class Solution {
public:
    bool rotateString(string s, string goal) {
        for(int i = 0 ; i < s.size() ; i++){
            char temp = s[0];
            for(int j = 0 ; j < s.size()-1 ; j++){
                s[j] = s[j+1]; 
            }
            s[s.size()-1]=temp;
            if(s==goal)return true;
        }
        return false;
    }
};