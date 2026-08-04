class Solution {
  public:
    double minMaxDist(vector<int> &stations, int k) {
        // Code here
        if (stations.size() <= 1) return 0.0;

        vector<int> distances(stations.size() - 1, 0.0);
        priority_queue<pair<long double, int>> distancesqueue;
        for(int i = 0 ; i < stations.size()-1;i++){
            distancesqueue.push({(long double)stations[i+1]-stations[i], i});
        }
        for(int i = 1 ; i <= k ; i++){
            auto top = distancesqueue.top();
            distancesqueue.pop();
            int index = top.second;
            distances[index]++;
            long double newlength = (long double)(stations[index+1]-stations[index])/(distances[index]+1);
            distancesqueue.push({newlength,index});
        }
        auto ans = distancesqueue.top();
        return ans.first;
    }
};