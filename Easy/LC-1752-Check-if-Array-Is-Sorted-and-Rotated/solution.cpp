class Solution {
public:
    bool check(vector<int>& nums) {
        for(int i=0;i<nums.size()-1;i++){
            if(nums[i]>nums[i+1]){
                reverse(nums.begin(),nums.begin()+i+1);
                reverse(nums.begin()+i+1,nums.end());
                reverse(nums.begin(),nums.end());
                for(int j=0;j<nums.size()-1;j++){
                    if(nums[j]>nums[j+1]){
                        return false;
                    }
                }   
                return true;
            }
           
        }
        return true;

    }
};


