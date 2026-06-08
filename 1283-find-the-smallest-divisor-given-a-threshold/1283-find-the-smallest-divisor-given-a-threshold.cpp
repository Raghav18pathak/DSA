class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int maxu = *max_element(nums.begin(),nums.end());
        int low = 1,high = maxu;
        int ans= 0;
        while(low<=high){
            int mid = (high + low)/2;
            int count = 0;
            for(int j=0;j<nums.size();j++){
                count += ceil((double)nums[j]/mid);
            }
            if(count<=threshold){
                ans = mid;
                high = mid-1;
            }
            else low = mid+1;
        }
        return ans;
        
    }
};