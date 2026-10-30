class Solution {
  public:
    int countFreq(vector<int>& nums, int target) {
        // code here
        vector<int> ansvec = {-1,-1};
        int low =0;
        int high = nums.size()-1;
        if(nums.empty())return 0;
        while(low<=high){
            int mid = (low +high)/2;
            if (nums[mid]==target){
                ansvec[0]=mid;
                high = mid-1;
            }
            else if(nums[mid]>target){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        if(ansvec[0]==-1) return 0;
        low =0; high = nums.size()-1;
        while(low<=high){
            int mid=(low +high)/2;
            if (nums[mid]==target){
                ansvec[1]=mid;
                low = mid+1;
            }
            else if(nums[mid]>target){
                high = mid-1;
            }
            else{
                low = mid+1;
            }
        }
        int ans = ansvec[1]-ansvec[0]+1;
        return ans;
    }
};
