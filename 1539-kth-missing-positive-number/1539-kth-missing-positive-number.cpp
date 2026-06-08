class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int maxu = *max_element(arr.begin(),arr.end());
        int count = 0;
        int j = 0;
        for(int i = 1 ; i<=maxu+k;i++){
            if(j<arr.size()&&arr[j]==i){
                j++;
                continue;
            }
            else count ++;
            if(count == k) return i;
        }
        return -1;
    }
};