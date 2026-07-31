class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int low = 0, high = arr.size()-1;
        int ans = -1;
        while(low <= high){
            int mid = (low+high)/2;
            int missingcount = arr[mid]-(mid+1);
            if(missingcount<k)low = mid+1;
            else high = mid-1;
        }
        return high+1+k;
    }
};