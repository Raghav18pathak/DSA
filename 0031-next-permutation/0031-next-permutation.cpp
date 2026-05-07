class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int index = -1;
        for(int i=nums.size()-2;i>=0;i--){
            if(nums[i]<nums[i+1]){
                index = i;
                break;
            }
        }

        if(index == -1){
            reverse(nums.begin(),nums.end());
            return;
        }
        int small = INT_MAX;
        int smallind = -1;
        for(int i=index+1;i<nums.size();i++){
            if(nums[i]>nums[index]&&nums[i]<small){
                small = nums[i];
                smallind = i;
            }
        }
        swap(nums[index],nums[smallind]);
        sort(nums.begin()+index+1,nums.end());

    }
};