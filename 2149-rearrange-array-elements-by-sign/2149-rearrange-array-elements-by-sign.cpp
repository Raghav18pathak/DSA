class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        vector<int> temp1;
        vector<int> temp2;
        for(int i= 0;i<nums.size();i++){
            if(nums[i]>=0) temp1.push_back(nums[i]);
            else temp2.push_back(nums[i]);
        }
        for (int i = 0; i < nums.size() / 2; i++) {
            nums[2 * i] = temp1[i];     
            nums[2 * i + 1] = temp2[i]; 
        }
        return nums;
    }
};