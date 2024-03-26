/*
    如果vector<int> nums長度為3，則 缺的數字一定為1~4之間
    因為nums最多只有三個數字，所以答案一定會出現在1~4之間。
    loop 1 把1~3的數字放在index0~2之間，
    loop 2 檢查缺少哪一個數字
*/
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int sz = nums.size();
        for(int i = 0; i < nums.size(); ++i) { // O(N)
            if(nums[i] >= 1 && nums[i] <= sz && nums[i] != i + 1 && nums[i] != nums[nums[i] - 1]) {
                swap(nums[i], nums[nums[i] - 1]);
                --i;
            }
        }
        int ans = 1;
        for(int i = 0; i < nums.size(); ++i, ++ans) { // O(N)
            if(nums[i] != ans) return ans;
        }
        return ans;
    }
};
