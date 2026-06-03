class Solution {
  public:
    int findKRotation(vector<int> &nums) {
        // Code Here
        int minind = -1;
        int minum = INT_MAX;
        int low =0;
        int high= nums.size()-1;
        while(low<=high){
            int mid = (low + high)/2;
            if(nums[low]<= nums[mid]){
                if(nums[low]<minum){
                    minind = low;
                    minum = nums[low];
                }
                low = mid+1;
            }
            else{
                if(nums[mid]<minum){
                    minind = mid;
                    minum = nums[mid];
                }
                high = mid-1;
            }
        }
        return minind;
    }
};
