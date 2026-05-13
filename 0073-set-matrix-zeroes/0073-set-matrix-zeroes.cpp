class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<pair<int,int>> res;
        for(int i= 0;i<matrix.size();i++){
            for(int j=0;j<matrix[0].size();j++){
                if(matrix[i][j]==0){
                    res.push_back({i,j});
                }
            }
        }
        for(int i=0;i<res.size();i++){
            for(int j = 0;j<matrix[0].size();j++){
                if(matrix[res[i].first][j]!=0) matrix[res[i].first][j]=0; 
            }
            for(int j = 0;j<matrix.size();j++){
                if(matrix[j][res[i].second]!=0) matrix[j][res[i].second]=0; 
            }
        }
    }
};