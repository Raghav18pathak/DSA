class Solution {
public:
    int sum =0, count =0;
    int subarraySum(vector<int>& nums, int k) {
        for(int i = 0;i<nums.size();i++){
            int sum =0;
            for(int j = i;j<nums.size();j++){
                sum = sum + nums[j];
                if(sum == k)count ++;
            }
        }
        return count; 
    }
};