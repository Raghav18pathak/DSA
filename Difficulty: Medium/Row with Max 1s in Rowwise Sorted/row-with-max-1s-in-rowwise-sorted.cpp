class Solution {
  public:
    int rowWithMax1s(vector<vector<int>> &arr) {
        // code here
        int max=0;
        int maxind = -1;
        for(int i = 0 ; i < arr.size();i++){
            int low = 0;
            int high = arr[i].size()-1;
            int ans=-1;
            while(low<=high){
                int mid = (low+high)/2;
                if(arr[i][mid]==1){
                    ans = mid;
                    high = mid-1;
                }
                else low = mid+1;
            }
            int count = 0;
            if(ans != -1) {
                count = arr[i].size() - ans;
            }
            if(max<count){
                max = count;
                maxind = i;
            }
        }
        return maxind;
    }
};