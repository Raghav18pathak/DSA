class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int maxu = *max_element(piles.begin(),piles.end());
        int ans = 0;
        int low = 1, high = maxu;
        while(low<=high){
            int mid = (low+high)/2;
            long long totalhours = 0;
            for(int j = 0 ; j<piles.size();j++){
                if(piles[j]%mid!=0) totalhours += ((piles[j]/mid) + 1);
                else totalhours += (piles[j]/mid);
            }
            if(totalhours<=h){
                ans = mid;
                high = mid-1;
            }
            else low = mid+1;
        }
        return ans;
    }
};