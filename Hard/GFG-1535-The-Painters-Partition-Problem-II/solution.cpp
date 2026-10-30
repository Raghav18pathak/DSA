class Solution {
  public:
    int minTime(vector<int>& arr, int k) {
        // code here
        int maxu = INT_MIN;
        int sum = 0;
        for(int i = 0 ; i < arr.size() ; i++){
            sum += arr[i];
            maxu = max(maxu,arr[i]);
        }
        int low = maxu , high = sum;
        int ans = 0;
        while(low<=high){
            int mid = (low+high)/2;
            int grp = 1;
            int sum = 0;
            for(int i = 0 ; i < arr.size() ; i++){
                if(sum + arr[i] > mid){
                    sum = arr[i];
                    grp++;
                }
                else sum +=arr[i];
            }
            if(grp>k) low = mid+1;
            else{
                ans = mid;
                high = mid-1;
            }
        }
        return ans;
    }
};