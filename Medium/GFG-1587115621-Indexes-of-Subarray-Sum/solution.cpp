class Solution {
  public:
    vector<int> subarraySum(vector<int> &arr, int target) {
        int n = arr.size();
        int current_sum = 0;
        int start = 0;

        for (int end = 0; end < n; end++) {
            // Add current element to our window sum
            current_sum += arr[end];

            // If current_sum is greater than target, 
            // shrink the window from the left until it's <= target
            while (current_sum > target && start < end) {
                current_sum -= arr[start];
                start++;
            }

            // Check if we found the target
            if (current_sum == target) {
                return {start + 1, end + 1}; // Return 1-based indices
            }
        }

        // If we finish the loop without finding the sum, return -1
        return {-1};
    }
};