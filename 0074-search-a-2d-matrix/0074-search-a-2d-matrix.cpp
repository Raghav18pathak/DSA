class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();
        int row = -1;
        int low = 0,high = n-1;
        while(low<=high){
            int mid = (low + high)/2;
            if(matrix[mid][m-1]>=target){
                row = mid;
                high = mid-1;
            }
            else low = mid+1;
        }
        if (row ==-1) return false;
        low = 0 , high = matrix[row].size()-1;
        while(low<=high){
            int mid = (low+high)/2;
            if(matrix[row][mid]==target)return true;
            else if(matrix[row][mid]>target)high = mid-1;
            else low = mid+1;
        }
        return false;
    }
};