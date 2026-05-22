class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        set<vector<int>> st;
        
        for(int i = 0;i<nums.size();i++){
            for(int j = i+1;j<nums.size();j++){
                set<long long> stw;
                for(int k = j+1;k<nums.size();k++){
                    long long sum = (long long)nums[i] + nums[j] + nums[k];  
                    long long rem = (long long)target-sum;
                    if(stw.find(rem)!=stw.end()){
                        vector<int> temp = {nums[i],nums[j],nums[k],(int)rem}; 
                        sort(temp.begin(),temp.end());
                        st.insert(temp);
                    }
                    stw.insert(nums[k]);
                }
            }
        }
        return vector<vector<int>> (st.begin(),st.end());
    }
};