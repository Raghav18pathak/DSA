class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if((long long)m*k>bloomDay.size()) return -1;
        int maxu = *max_element(bloomDay.begin(),bloomDay.end());
        int minu = *min_element(bloomDay.begin(),bloomDay.end());
        int ans;
        while(minu<=maxu){
            int mid = (minu+maxu)/2;
            int booqueCount = 0, flowerCount = 0;
            for(int j = 0 ; j < bloomDay.size(); j++){
                if(bloomDay[j]<=mid){
                   flowerCount++;
                   if(flowerCount == k){
                      flowerCount = 0;
                      booqueCount++;
                  }
                }
                else flowerCount = 0;
            }
            if(booqueCount>=m){
                ans = mid;
                maxu = mid-1;
            }
            else{
                minu = mid+1;
            }
        }
        return ans;
    }
};