int longestSubarrayWithSumK(vector<int> a, long long k) {
    // Write your code here
    int length = 0;
    for(int i=0;i<a.size();i++){
        long long sum=0;
        int count =0;
        for(int j=i;j<a.size();j++){
            sum = sum+a[j];
            count ++;
            if(sum == k && count > length){
                length = count;
            }
            if(sum>k) break;
        }
    }
    return length;
}