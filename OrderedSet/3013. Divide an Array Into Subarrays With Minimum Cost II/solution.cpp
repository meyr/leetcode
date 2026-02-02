/*
 *   把nums分成 k 個 subarray, 第二個subarray和最後一個subarray開頭index不能超過dist
 *
 *   1. 第一個subarray一定是index = 0
 *   2. 先不考慮 dist, 從index = 1開始找到 k - 1個最小的nums[i]就是解答
 *   3.                所以可以使用minheap和maxheap, 把數值先丟到minheap再把minheap.top()丟到maxheap, 如果maxheap.size() > k - 1, 再把maxheap.top()丟回minheap
 *                     這樣maxheap裡面就是k - 1個最小的數值
 *
 *   4. 考慮dist, 如果有dist就是一個slinding window, 進入window才需要放入minheap, 離開window就必須先移除
 *   5. 改使用multiset方便移除
 */
class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        long long ans {LLONG_MAX}, cur{};
        //  i...i + dist
        multiset<int> maxheap, minheap;
        for(int i = 1; i < nums.size(); ++i) {
            if(i > dist + 1) {                  // 移除離開window的數值
                int t = nums[i - dist - 1];
                auto it = minheap.find(t);
                if(it != minheap.end())         // 如果再minheap內找到直接移除
                    minheap.erase(it);
                else {                          // 如果再maxheap內找到要記得更新cur
                    it = maxheap.find(t);
                    cur -= t;
                    maxheap.erase(it);
                }
            }
            minheap.insert(nums[i]);            // 放入nums[i], 先丟入minheap, 再把最小值(minheap.top)丟入maxheap
            {
                auto it = minheap.begin();
                maxheap.insert(*it);
                cur += *it;
                minheap.erase(it);
            }
            if(maxheap.size() > k - 1) {        // 如果maxheap超過k - 1, 把最大值(maxheap.top)丟回minheap
                auto it = prev(maxheap.end());
                cur -= *it;
                minheap.insert(*it);
                maxheap.erase(it);
            }
            if(i >= 1 + dist)                   // 統計目前最小的maxheap和
                ans = min(ans, cur);
        }
        return ans + nums[0];
    }
};
