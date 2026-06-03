class Solution {
public:
    int findMin(vector<int>& nums) {
        int minu = INT_MAX, low = 0, high = nums.size()-1;
        while(low<=high){
            int mid = (low+high)/2;
            minu = min(minu,nums[mid]);
            if(nums[low]>nums[mid])high = mid-1;
            else if(nums[mid]>nums[high]) low = mid+1;
            if(nums[low]<=nums[mid]&& nums[mid]<=nums[high]) {
                minu = min(minu, nums[low]);
                break;
            }
        }
        return minu;
    }
};