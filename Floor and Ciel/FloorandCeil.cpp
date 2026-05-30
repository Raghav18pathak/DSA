/*
    Problem: Ceil The Floor
    Link: https://www.naukri.com/code360/problems/ceil-the-floor_630291
    Time Complexity: O(log N)
    Space Complexity: O(1)
    
    Description: Finds the Floor (largest element <= x) and 
                 Ceiling (smallest element >= x) in a sorted array.
*/

#include <vector>
#include <utility>

using namespace std;

pair<int, int> getFloorAndCeil(vector<int> &a, int n, int x) {
    pair<int, int> ans = {-1, -1};
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (a[mid] == x) {
            // Target found: it is both its own floor and ceiling
            ans.first = a[mid];
            ans.second = a[mid];
            return ans;
        } 
        else if (a[mid] < x) {
            // Potential floor found, look for a larger one to the right
            ans.first = a[mid];
            low = mid + 1;
        } 
        else {
            // Potential ceiling found, look for a smaller one to the left
            ans.second = a[mid];
            high = mid - 1;
        }
    }
    return ans;
}