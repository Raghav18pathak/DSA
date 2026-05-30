# Ceil The Floor (Sorted Array)

## Problem Statement
Given a sorted array `a` of `n` integers and an integer `x`, find the **floor** and **ceiling** of `x`.

- **Floor**: The largest element in the array which is smaller than or equal to `x`.
- **Ceiling**: The smallest element in the array which is greater than or equal to `x`.

If a floor or ceiling doesn't exist, return `-1`.

## My Approach
I implemented a **One-Pass Binary Search** to solve this in $O(\log n)$ time.

### Logic:
1. **Target Found (`a[mid] == x`)**: If the middle element matches `x`, it is immediately both the floor and the ceiling. I return the pair instantly.
2. **Value is Smaller (`a[mid] < x`)**: This is a candidate for the **floor**. I store it in `ans.first` and move the `low` pointer to the right (`mid + 1`) to see if a larger value still satisfies the floor condition.
3. **Value is Larger (`a[mid] > x`)**: This is a candidate for the **ceiling**. I store it in `ans.second` and move the `high` pointer to the left (`mid - 1`) to see if a smaller value still satisfies the ceiling condition.

---

## Complexity
- **Time Complexity**: $O(\log N)$ - Because we are halving the search space in each iteration.
- **Space Complexity**: $O(1)$ - Only a few variables are used regardless of input size.