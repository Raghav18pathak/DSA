class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows);
        for(int i=1;i<=numRows;i++){
            if(i==1){
                res[i-1].push_back(1);
            }
            else if(i==2){
                res[i-1].push_back(1);
                res[i-1].push_back(1);
            }
            else{
                res[i-1].push_back(1);
                int temp1=0 , temp2 = 1;
                for(int k=0;k<res[i-2].size()-1;k++){
                    res[i-1].push_back(res[i-2][temp1]+res[i-2][temp2]);
                    temp1++;
                    temp2++;
                }
                res[i-1].push_back(1);
            }
        }
        return res;
    }
};