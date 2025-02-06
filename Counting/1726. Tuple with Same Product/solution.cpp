/*  因為數字不會有重複 所以不需要考慮 a, b, c, d, 會有相等的情況
 *  只要找出一組 就會有8組的答案
 *
 *  [a, b, c, d]
 *  a*b, c*d
 *  b*a, c*d
 *  a*b, d*c
 *  b*a, d*c

 *  c*d, a*b
 *  c*d, b*a
 *  d*c, a*b
 *  d*c, b*a   --> 8

 *  0  1  2  3   4
 *  1, 2, 4, 5, 10          2->(0, 1)
 *  *  *                    4->(0, 2)
 *  *     *                 5->(0, 3)
 *  *        *             10->(0, 4)(2, 3)
 *  *            *

 *     *  *                 8->(1, 2)
 *     *     *
 *     *          *        20->(1, 4)(2, 3)

 *        *  *
 *        *       *        40->(2, 4)

 *           *    *        50->(3, 4)
 *
 */

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        // 找出所有的 nums[i] * nums[j]的組合
        unordered_map<int, vector<vector<int>>> m;
        for(int i = 0; i < nums.size(); ++i)            
            for(int j = i + 1; j < nums.size(); ++j)
                m[nums[i] * nums[j]].push_back({i, j});

        // 計算每個組合中a, b, c, d不相同的情況
        int ans{};
        for(auto& ref : m) {
            vector<vector<int>> vvi = ref.second;
            for(int i = 0; i < vvi.size(); ++i) {
                for(int j = i + 1; j < vvi.size(); ++j) {
                    unordered_set<int> us;
                    us.insert(vvi[i][0]);
                    us.insert(vvi[i][1]);
                    us.insert(vvi[j][0]);
                    us.insert(vvi[j][1]);
                    if(us.size() == 4) ans += 8;
                }
            }
        }
        return ans;
    }
};
/* 因為nums[i]都不一樣 所以不會有nums[a]*nums[b] == nums[b]*nums[c] --> nums[a] == nums[c] 不可能發生
 * 所以不需要計算是否會有一樣的情況 這樣也不用特別儲存vector<vector<int>>
 * 簡化的結果
 *
 * time  : O(N^2 + N) = O(N^2)
 * space : O(N^2)
 */
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> m;
        for(int i = 0; i < nums.size(); ++i)
            for(int j = i + 1; j < nums.size(); ++j)
                m[nums[i] * nums[j]]++;
        int ans{};
        for(auto& ref : m)
            ans += ref.second * (ref.second - 1) * 4;

        return ans;
    }
};
