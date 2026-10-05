class Solution {
  public:
    int floorSqrt(int n) {
        // code here
       int low =1, high = n;
       int ans = n;
       while(low<= high){
           int mid = (low + high)/2;
           if(mid*mid>n)high = mid-1;
           else{
               ans = mid;
               low = mid+1;
           }
       }
       return ans;
    }
};
