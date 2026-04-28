🔗 Longest Subarray With Sum KEasyProblem StatementYou are given an array 'a' of size 'n' and an integer 'k'.Find the length of the longest subarray of 'a' whose sum is equal to 'k'.Example:Input: n = 7, k = 3'a' = [1, 2, 3, 1, 1, 1, 1]Output: 3Explanation: Subarrays whose sum = '3' are:[1, 2], [3], [1, 1, 1] and [1, 1, 1]Here, the length of the longest subarray is 3, which is our final answer.My Solution (Brute Force)C++int longestSubarrayWithSumK(vector<int> a, long long k) {
    int length = 0;
    for(int i=0; i<a.size(); i++){
        long long sum = 0;
        int count = 0;
        for(int j=i; j<a.size(); j++){
            sum = sum + a[j];
            count++;
            if(sum == k && count > length){
                length = count;
            }
            if(sum > k) break;
        }
    }
    return length;
}
Complexity Analysis:Time Complexity: $O(n^2)$Space Complexity: $O(1)$
