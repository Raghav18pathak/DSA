/*
    Problem: Implement Upper Bound
    Link: https://www.naukri.com/code360/problems/implement-upper-bound_816538
    Time Complexity: O(log N)
    Space Complexity: O(1)
    
    Description: Finds the first index 'ind' where arr[ind] > x.
*/

#include <vector>
using namespace std;

int upperBound(vector<int> &arr, int x, int n) {
    int low = 0, high = n - 1;
    int ans = n;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Condition for Upper Bound: strictly greater than x
        if (arr[mid] > x) {
            ans = mid;         // This is a candidate
            high = mid - 1;    // Look left for an even smaller index
        } else {
            low = mid + 1;     // Too small or equal to x, look right
        }
    }
    return ans;
}