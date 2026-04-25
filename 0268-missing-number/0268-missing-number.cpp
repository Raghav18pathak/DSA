class Solution {
public:
    
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int count = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=count){
                return i;
            }
            count++;
        }
        return nums.size();

    }
};