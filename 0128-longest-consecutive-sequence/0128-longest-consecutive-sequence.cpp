class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set <int> st; 
        if (nums.size() == 0) return 0;
        int longest = 1; 
        for(int i =0;i<nums.size();i++){
            st.insert(nums[i]);
        }
        for(auto i : st){
            if(st.find(i-1)==st.end()){
                int count =1;
                int x = i;
                while(st.find(x + 1) != st.end()){
                    count ++;
                    x++;
                }
                longest = max(longest,count);
            }
        }
        return longest;
    }
};