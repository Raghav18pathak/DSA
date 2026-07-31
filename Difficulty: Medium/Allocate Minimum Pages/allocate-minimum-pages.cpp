class Solution {
  public:
    int findPages(vector<int> &arr, int k) {
        // code here
        if(k > arr.size()) return -1;
        long long sum = 0;
        int maxu = INT_MIN;
        for(int i = 0; i<arr.size();i++){
            sum += arr[i];
            maxu = max(maxu , arr[i]);
        }
        long long low = maxu , high = sum;
        long long ans = sum;
        while(low<=high){
            long long mid = (low+high)/2;
            int studentcount = 1;
            long long pages = 0;
            for(int i = 0; i < arr.size() ; i++){
                if(pages + arr[i] <= mid) pages += arr[i];
                else{
                    studentcount++;
                    pages = arr[i];
                }
            }
            
            if(studentcount<=k){
                ans = min(ans,mid);
                high = mid-1;
            }
            else{
                low = mid+1;
            }
            
        }
        return ans;
    }
};