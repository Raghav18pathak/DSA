class Solution {
  public:
    int aggressiveCows(vector<int> &arr, int k) {
        // code here
        sort(arr.begin(),arr.end());
        int maxu = arr[arr.size()-1]-arr[0];
        int ans = 0;
        int low = 1 , high = maxu;
        while(low<=high){
        int mid = (low + high)/2;
            int countcows = 1;
            int lastcowplaced = 0;
            for(int j = 1;j<arr.size();j++){
                if(arr[j]-arr[lastcowplaced]>=mid){
                    lastcowplaced = j;
                    countcows++;
                }
                if(countcows == k)break;
            }
            if(countcows==k){ 
                low = mid+1;
                ans = mid;
            }
            else high = mid-1;
        }
        return ans;
    }
};