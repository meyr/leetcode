/*  找出相同數字最近距離 一定是和他出現的最早和最晚有關
 *
 *
 *  _, _, x, _, _, x, _, _, x
 *       /|\               /|\
 *        |                 +----- 從這個x往前看 最短距離只會發生在第一個x和最後一個x
 *        |                        所以使用unordered_map<int, pair<int, int>> 來記錄數值的兩個極值index
 *        +---- 同理也要從某個數字向後看
 *
 * time  : O(N)
 * sapce : O(N)
 */
class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        unordered_map<int, pair<int, int>> um;
        int sz = nums.size();
        vector<int> minDist(sz, sz);
        for(int i = 0; i < sz; ++i) {
            int& n = nums[i];
            if(!um.count(n))
                um[n] = {i, i};
            else {
                minDist[i] = min({minDist[i], abs(um[n].first - i + sz) % sz, abs(i - um[n].second)});
                um[n].first = min(um[n].first, i);
                um[n].second = max(um[n].second, i);
            }
        }
        um.clear();
        for(int i = sz - 1; i >= 0; --i) {
            int& n = nums[i];
            if(!um.count(n))
                um[n] = {i, i};
            else {
                minDist[i] = min({minDist[i], abs(um[n].first - i + sz) % sz, abs(i - um[n].second + sz) % sz});
                um[n].first = min(um[n].first, i);
                um[n].second = max(um[n].second, i);
            }
        }

        vector<int> ans;
        for(auto& q : queries)
            ans.push_back(minDist[q] == sz ? -1 : minDist[q]);
        return ans;
    }
};

