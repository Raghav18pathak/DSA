class Solution {
public:
    int shipWithinDays(vector<int>& nums, int days) {
        int sum = 0;
        for(int i=0;i<nums.size();i++){
            sum += nums[i];
        }
        int maxu = *max_element(nums.begin(),nums.end());
        int low = maxu , high = sum;
        int ans= -1;
        while(low<=high){
            int mid = (low+high)/2;
            int innerSum=0,daysCount=1;
            for(int j = 0;j<nums.size();j++){
                if(innerSum+nums[j]<=mid) innerSum +=nums[j];
                else {
                    innerSum = nums[j];
                    daysCount++;
                }
            }
            
            if(daysCount > days){
                low = mid+1;
            }
            else{
                ans = mid;
                high = mid-1;
            }
        }
        return ans;
    }
};