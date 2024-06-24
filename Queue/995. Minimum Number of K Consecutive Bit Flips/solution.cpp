/*
 * 參考 : https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/solutions/239284/c-greedy-stack-and-o-1-memory/
 *
 * 1. 每翻一個nums[i] 則會影響至nums[i + k - 1]
 * 2. 數數看queue的大小 就會知道nums[i]需不需要flip
 * 3. 如果需要翻就把i+k-1也推入queue
 * 4. 把超過影響範圍的 flips.front() <= i 丟掉
 *
 * time  : O(N)
 * space : O(K), 因為i>k就會開始丟
 */
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k, int res = 0) {
        queue<int> flips;
        for(auto i = 0; i < nums.size(); ++i) {
            if(nums[i] != flips.size() % 2 ? 0 : 1) { // 數有幾次需要被flip
                ++res;
                flips.push(i + k - 1); // 從i ~ i + k - 1都被需被flip
            }
            if(!flips.empty() && flips.front() <= i) flips.pop(); // 已經超過flip的範圍->丟掉
        }
        return flips.empty() ? res : -1;
    }
};
