class Solution {
public:
    int maxProfit(vector<int>& nums) {
        int buy = 0;
        int res = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]<nums[buy]){
                buy = i;
            }
            if(nums[i]-nums[buy]>res){
                res = nums[i]-nums[buy];
            }
        }
         return res;
    }
};