# Implement Lower Bound

## Problem Statement
You are given an array 'arr' sorted in non-decreasing order and a number 'x'. You must return the index of the lower bound of 'x'.

**Note:**
1. For a sorted array 'arr', 'lower_bound' of a number 'x' is defined as the smallest index 'idx' such that the value 'arr[idx]' is not less than 'x'.
2. If all numbers are smaller than 'x', then 'n' should be the 'lower_bound' of 'x', where 'n' is the size of the array.

**Expected Time Complexity:** O(log(n))

---

## My Approach
Used **Binary Search** to achieve $O(\log n)$ efficiency. 
- Instead of returning immediately when `arr[mid] == x`, I stored the index in `ans` and moved the `high` pointer to `mid - 1`. 
- This ensures that we find the **first** occurrence (the smallest index) that satisfies the condition.