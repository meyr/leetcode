/*  看到重複的就把後面的搬到前面
 *
 *  time  : O(N^2)
 *  space : O(1)
 */
 class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int ans{}, sz = nums.size(), i = 1;
        while(i < sz) {
            if(nums[i] == nums[i - 1]) {
                int j = i + 1, len = 0;
                while(j < sz && nums[j] == nums[i]) ++j;
                if(j - i > 1) {
                    int _sz = sz;
                    sz -= j - i - 1;
                    for(int k = i + 1; j < _sz; ++j, ++k)
                        nums[k] = nums[j];
                }

            }
            i++;
        }
        return i;
    }
};
/*  參考解答:https://leetcode.cn/problems/remove-duplicates-from-sorted-array-ii/solutions/702644/shan-chu-pai-xu-shu-zu-zhong-de-zhong-fu-yec2/
 *  
 *  使用快慢指針就可以達到此效果
 *
 *  time  : O(N)
 *  space : O(1)
 */
 class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int sz = nums.size();
        if(sz <= 2) return 2;
        int slow = 2, fast = 2;
        while(fast < sz) {
            if(nums[slow - 2] != nums[fast]) {
                nums[slow] = nums[fast];
                ++slow;
            }
            ++fast;
        }
        return slow;
    }
};
