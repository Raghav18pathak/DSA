/*
    Problem: Implement Lower Bound
    Link: https://www.naukri.com/code360/problems/lower-bound_816511
    Time Complexity: O(log N)
    Space Complexity: O(1)
*/

#include <vector>
#include <algorithm>
using namespace std;

int lowerBound(vector<int> arr, int n, int x) {
    int low = 0, high = n - 1;
    int ans = n;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Lower Bound definition: Smallest index where arr[mid] >= x
        if (arr[mid] >= x) {
            ans = mid;        // Potential answer found
            high = mid - 1;   // Look left for a smaller index
        } else {
            low = mid + 1;    // Value too small, look right
        }
    }
    return ans;
}