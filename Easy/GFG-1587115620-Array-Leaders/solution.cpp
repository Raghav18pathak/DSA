

class Solution {
  public:
    vector<int> leaders(vector<int>& nums) {
        // code here
        int largest = nums[nums.size()-1];
        for(int i=nums.size()-1;i>=0;i--){
            if(nums[i]>=largest){
                largest = nums[i];
            }
            else{
                nums.erase(nums.begin()+i);
                i++;
            }
        }
        return nums;
    }
};