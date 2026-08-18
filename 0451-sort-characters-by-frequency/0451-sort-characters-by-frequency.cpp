class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int> mpp;
        for(auto ch : s){
            mpp[ch]++;
        }
        vector<pair<char,int>> v(mpp.begin(),mpp.end());
        sort(v.begin() , v.end() , [](const pair<char, int> &a , const pair<char, int> &b){
            return a.second>b.second;
        });
        string ans;
        for(int i = 0 ; i<v.size() ; i++){
            for(int j = 0 ; j < v[i].second ; j++){
                ans.push_back(v[i].first);
            }
        }
        return ans;
    }
};