class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
        int sum = 0 ;
        int maxu = INT_MIN;
        for(int i = 0;i<nums.size();i++){
            sum+=nums[i];
            maxu = max(maxu , nums[i]);      
        }
        int low = maxu , high = sum;
        int ans = 0;
        while(low<=high){
            int mid = (low+high)/2;
            int grp = 1;
            int sum = 0;
            for(int i = 0;i<nums.size();i++){
                if(sum + nums[i]<=mid) sum += nums[i];
                else{
                    sum = nums[i];
                    grp++;
                }
            }
            if(grp > k) low = mid+1;
            else{
                ans = mid;
                high = mid-1;
            }
        }
        return ans;
              

    }
};