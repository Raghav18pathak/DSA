class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_multimap<int,int> mpp;
        for(int i=0;i<nums.size();i++){
            int rem = target-arr[i];
                if(mpp.find(rem)!=mpp.end()){
                    return {mpp[rem],i}
                }
                mpp[sum]=i;
            }
        }
        return {};
    }
};