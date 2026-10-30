int longestSubarrayWithSumK(vector<int> a, long long k) {
    // Write your code here
    int result = 0;
    long long sum=0;
    int j=0;
    for(int i=0;i<a.size();i++){
        sum = sum + a[i];
        if(sum == k && i-j+1 > result) result = i-j+1;
        if(sum > k){
            sum = sum - a[j];
            sum = sum - a[i];
            j++;
            i--;
        }
    }
    return result;
}
