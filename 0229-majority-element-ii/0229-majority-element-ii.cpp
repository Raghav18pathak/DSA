class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> ans;
        unordered_map<int,int> count;
        for(int i=0;i<nums.size();i++){
            if(count.find(nums[i])==count.end()) count[nums[i]]=1;
            else count[nums[i]]++;
        }
        for(auto pair : count){
            if(pair.second>nums.size()/3){
                ans.push_back(pair.first);
            }
        }
        return ans;
    }
};