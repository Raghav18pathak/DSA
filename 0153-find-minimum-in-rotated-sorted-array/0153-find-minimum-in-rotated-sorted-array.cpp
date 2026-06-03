class Solution {
public:
    int findMin(vector<int>& nums) {
        int minu = INT_MAX, low = 0, high = nums.size()-1;
        while(low<=high){
            int mid = (low+high)/2;
            if(nums[low]<=nums[mid]){
                minu = min(minu,nums[low]);
                low = mid+1;
            }
            else{
                minu = min(minu,nums[mid]);
                high = mid-1;
            }
        }
        return minu;
    }
};