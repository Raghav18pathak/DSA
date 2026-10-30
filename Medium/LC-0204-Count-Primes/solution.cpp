class Solution {
public:
    int countPrimes(int n) {
        if(n<=2)return 0;
        int cnt = n-2;
        vector<char> s(n,1);
        for(int i = 2; i*i < n; i++){
            if(s[i]==1){
                for(int j = i*i ; j<n;j+=i){
                    if(s[j]==1){
                        s[j] =0;
                        cnt--;
                    }
                }
            }
        }
        return cnt;
   }
};