class Solution {
  public:
    int nthRoot(int n, int m) {
        // Code here
        int ans = -1;
        for(int i=0;i<=m;i++){
            int num = 1 ;
            for(int j = 1;j<=n;j++){
                num *= i;
            }
            if(num>m) break;
            if(num == m){
                ans = i;
                break;
            }
        }
        return ans;
    }
};