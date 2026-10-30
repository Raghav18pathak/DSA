class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        int leftsize = (nums1.size()+nums2.size()+1)/2;
        int low = 0 , high = nums1.size();
        while(low<=high){
            int cut1 = (low+high)/2;
            int cut2 = leftsize - cut1;
            int left1 = (cut1==0) ? INT_MIN : nums1[cut1-1];
            int right1 = (cut1==nums1.size()) ? INT_MAX : nums1[cut1];
            int left2 = (cut2==0) ? INT_MIN : nums2[cut2-1];
            int right2 = (cut2==nums2.size()) ? INT_MAX : nums2[cut2];
            if(left1<=right2 && left2<=right1){
                if((nums1.size()+nums2.size())%2==1) return max(left1,left2);
                else return ((double)max(left1, left2) + (double)min(right1, right2)) / 2.0;
            }
            else if(left1>right2) high = cut1-1;
            else low = cut1+1;
        }
        return 0.0;
    }
};