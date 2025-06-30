/*  這題為什麼可以先sorting?
 *
 *  因為題目是找subsequence 所以符合題目的subsequence都會是相鄰數值 例如其中一個解答是 2, 2, 2, 3, 3
 *  不管是2, 3, 2, 2, 3 還是 3, 2, 2, 2, 3 等等的變化 我們只要sorting就可以找到最原始從小到大的排列
 *
 *  所以先sorting再使用slinding window找出答案
 *
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(logN)
 *
 */
class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(begin(nums), end(nums));
        int ans{};
        for(int left = 0, right = 0; right < nums.size(); ++right) {
            while(left < right && nums[right] - nums[left] > 1)
                left++;
            if(nums[right] - nums[left] == 1)
                ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
/*  另一種解法 統計所有的數字個數  
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    int findLHS(vector<int>& nums) {
        unordered_map<int, int> um;
        for(auto& n : nums) um[n]++;
        int ans{};
        for(auto& ref : um)
            if(um.count(ref.first - 1))
                ans = max(ans, ref.second + um[ref.first - 1]);
        return ans;
    }
};
