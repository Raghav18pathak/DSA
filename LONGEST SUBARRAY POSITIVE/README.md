# 🔗 [Longest Subarray With Sum K](https://www.naukri.com/code360/problems/longest-subarray-with-sum-k_6682399)

## **Difficulty: Easy / Medium**

---

### **Problem Statement**

You are given an array **'a'** of size **'n'** and an integer **'k'**.
Find the length of the longest subarray of **'a'** whose sum is equal to **'k'**.

### **Example:**
- **Input:** `n = 7`, `k = 3`
- **Array:** `[1, 2, 3, 1, 1, 1, 1]`
- **Output:** `3`

---

### **My Solution (Optimal Sliding Window)**


```cpp
/* 
 * Time Complexity: O(n) - Each element is visited at most twice (by i and j)
 * Space Complexity: O(1) - Constant extra space used
 */
int longestSubarrayWithSumK(vector<int> a, long long k) {
    int n = a.size();
    int result = 0;
    long long sum = 0;
    int j = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];

        // Shrink window from the left if sum exceeds k
        while (sum > k && j <= i) {
            sum -= a[j];
            j++;
        }

        // Check if current window sum matches target k
        if (sum == k) {
            result = max(result, i - j + 1);
        }
    }
    return result;
}
