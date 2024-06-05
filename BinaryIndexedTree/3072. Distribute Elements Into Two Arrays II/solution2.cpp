/*
 *  使用binary search來計算greaterCount(arr, val)
 *
 *  time  : O(N^2)
 *  space : O(N)
 */
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> arr1, arr2, sarr1, sarr2;
        arr1.push_back(nums[0]);
        sarr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        sarr2.push_back(nums[1]);
        for(int i = 2; i < nums.size(); ++i) { //O(N(logN + N)) = O(N^2)
            auto it1 = upper_bound(begin(sarr1), end(sarr1), nums[i]);
            int cnt1 = sarr1.end() - it1;
            auto it2 = upper_bound(begin(sarr2), end(sarr2), nums[i]);
            int cnt2 = sarr2.end() - it2;
            if(cnt1 > cnt2) {
                arr1.push_back(nums[i]);
                sarr1.insert(it1, nums[i]);
            } else if(cnt2 > cnt1) {
                arr2.push_back(nums[i]);
                sarr2.insert(it2, nums[i]);
            } else {
                if(arr1.size() <= arr2.size()) {
                    arr1.push_back(nums[i]);
                    sarr1.insert(it1, nums[i]);                    
                } else {
                    arr2.push_back(nums[i]);
                    sarr2.insert(it2, nums[i]);                    
                }
            }

        }
        for(auto& n : arr2) arr1.push_back(n);
        return arr1; 
    }
};
