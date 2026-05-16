class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> prefixcount;
        int sum =0, count =0;
        prefixcount[0]=1;
        for(int i = 0;i<nums.size();i++){
            sum += nums[i];
            int rem = sum - k;
            if(prefixcount.find(rem)!=prefixcount.end()){
                count += prefixcount[rem];
            }
            if(prefixcount.find(sum)!=prefixcount.end()){
                prefixcount[sum]++;
            }
            else{
                prefixcount[sum] = 1;
            }
        }
        return count; 
    }
};