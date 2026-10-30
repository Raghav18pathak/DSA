class Solution {
  public:
    int maxLength(vector<int>& arr) {
        // code here
        unordered_map<int,int> mpp;
        int sum =0;
        int length =0;
        for(int i=0;i<arr.size();i++){
            sum = sum+arr[i];
            if(sum==0)length = i+1;
            if(mpp.find(sum)!=mpp.end()){
                length = max(length,i-mpp[sum]);
            }
            else{
                mpp[sum]=i;
            }
        }
        return length;
    }
};