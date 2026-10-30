class Solution {
  public:
    int longestSubarray(vector<int>& arr, int k) {
        // code here
        unordered_map<long long, int> mpp;
        long long sum = 0;
        int result =0;
        for(int i=0;i<arr.size();i++){
            sum += arr[i];
            if(sum == k) result = max(result,i+1);
            long long rem = sum -k;
            if(mpp.find(rem)!=mpp.end()) result = max(result, i-mpp[rem]); 
            if(mpp.find(sum)==mpp.end()) mpp[sum] = i;
        }
        return result;
        
    }
};