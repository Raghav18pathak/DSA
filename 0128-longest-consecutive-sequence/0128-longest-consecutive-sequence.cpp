class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        sort(nums.begin(),nums.end());
        int length = 1;
        int count = 1;
        for(int i = 1;i<nums.size();i++){
            if(nums[i-1]!=nums[i]){
                if(nums[i-1]+1==nums[i]){
                    count ++ ;
                    length = max(length, count);
                }
                else count = 1;
            }
        }
        return length;
    }
};