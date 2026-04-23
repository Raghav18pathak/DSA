class Solution {
public:
    bool check(vector<int>& nums) {
        for(int i=0;i<nums.size()-1;i++){
            if(nums[i]>nums[i+1]){
                vector<int> temp(nums.size());
                for(int j =0;j<=i;j++){
                    temp[j]=nums[j];
                }
                int count =0;
                int count1 = i+1;
                while(count1<=nums.size()-1){
                    nums[count]=nums[count1];
                    count++;
                    count1++;
                }
                count1=0;
                for(int j=count;j<nums.size();j++){
                    nums[j]=temp[count1];
                    count1++;
                }
                for(int j=0;j<nums.size()-1;j++){
                    if(nums[j]>nums[j+1]){
                        return false;
                    }
                }   
                return true;
            }
           
        }
        return true;

    }
};


