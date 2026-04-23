class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int i=0;
        for(int j=0;j<nums.size();j++){
            if(nums[j]>nums[i]){
                swap(nums[j],nums[i+1]);
                i++;
            }
        }
        return i+1;
    }
};