class Solution {
  public:
    long subarrayXor(vector<int> &nums, int k) {
        // code here
        int xorr = 0;
        int count = 0;
        unordered_map<int,int> mpp;
        mpp[0]=1;
        for(int i=0;i<nums.size();i++){
            xorr = xorr ^ nums[i];
            int remain = xorr ^ k;
            if(mpp.find(remain)!=mpp.end()){
                count += mpp[remain];
            }
            mpp[xorr]++;
        }
        return count;
    }
};