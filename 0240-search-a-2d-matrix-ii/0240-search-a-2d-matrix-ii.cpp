class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();
        int low = 0 , high = matrix.size()-1;
        int row= -1;
        while(low<=high){
            int mid = (low + high)/2;
            if(matrix[mid][m-1]>=target){
                row = mid;
                high = mid-1;
            }
            else low = mid+1;
        }
        if(row == -1) return false;
        for(int i = row ; i < n ; i++){
            low = 0 , high = m-1;
            while(low<=high){
                int mid = (low+high)/2;
                if(matrix[i][mid]==target)return true;
                else if(matrix[i][mid]>target)high = mid-1;
                else low = mid+1;
            }
        }
        return false;
    }
};