class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        int count1=0,count2=0,num1=INT_MIN,num2=INT_MIN;
        for(int i=0;i<nums.size();i++){
            if(count1==0 && nums[i]!=num2){
                count1=1;
                num1=nums[i];
            }
            else if(count2==0 && nums[i]!=num1){
                count2=1;
                num2=nums[i];
            }
            else if(nums[i]==num1) count1++;
            else if(nums[i]==num2) count2++;
            else{
                count1--;
                count2--;
            }
        }
        count1=0; count2=0;
        for(int i:nums){
            if(i==num1) count1++;
            else if(i==num2) count2++;
        }
        if(count1>nums.size()/3) ans.push_back(num1);
        if(count2>nums.size()/3) ans.push_back(num2);
        return ans;
    }
};