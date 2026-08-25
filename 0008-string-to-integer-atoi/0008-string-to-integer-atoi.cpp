class Solution {
public:
    int myAtoi(string s) {
        int ptr = 0;
        int sign = 1;
        while(ptr<s.size() && s[ptr]==' ') ptr++;
        if(ptr < s.size() && (s[ptr] == '-' || s[ptr]=='+')){
            if(s[ptr] == '-') sign = -1;
            ptr++;
        }
        long ans = 0;
        while(ptr<s.size() && isdigit(s[ptr])==true){
            ans = ans*10 + (s[ptr]-'0');
            if (sign * ans <= INT_MIN) return INT_MIN;
            if (sign * ans >= INT_MAX) return INT_MAX;
            ptr++;
        }
        ans = ans*sign;
        return ans;
    }
};