class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        vector<pair<int,int>> res;
        for(int i=0;i<matrix.size();i++){
            for(int j = 0;j<matrix[0].size();j++){
                if(matrix[i][j]==0){
                    for(int k = 0;k<matrix.size();k++){
                        if(matrix[k][j]!=0)res.push_back({k,j});
                    }
                    for(int k = 0;k < matrix[0].size();k++){
                        if(matrix[i][k]!=0)res.push_back({i,k});
                    }
                }
            }
        }
        for(int i=0;i<res.size();i++){
            matrix[res[i].first][res[i].second]=0;
        }
    }
};