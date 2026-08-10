class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i = 0 , j = 0;
        vector<int> mergednums;
        while(i < nums1.size() && j < nums2.size()){
            if(nums1[i]<=nums2[j]){
                mergednums.push_back(nums1[i]);
                i++;
            }
            else{
                mergednums.push_back(nums2[j]);
                j++;
            }
        }
        while(i<nums1.size()){
            mergednums.push_back(nums1[i]);
            i++;
        }
        while(j<nums2.size()){
            mergednums.push_back(nums2[j]);
            j++;
        }
        if(mergednums.size() % 2 == 0){
            int n1 = mergednums[(mergednums.size() - 1) / 2];
            int n2 = mergednums[((mergednums.size() - 1) / 2) + 1];
            return (n1 + n2) / 2.0; 
        }
        else{
            return mergednums[(mergednums.size() - 1) / 2];
        }
    }
};