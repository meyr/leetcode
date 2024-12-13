/*  根據value, index排序 再用unordered_set來mark訪問過的index
 *
 *  time  : O(N + NlogN + N) = O(NlogN)
 *  space : O(N + logN + N) = O(N) 
 */
class Solution {
public:
    long long findScore(vector<int>& nums) {
        vector<pair<int, int>> vp;
        int sz = nums.size();
        for(int i = 0; i < nums.size(); ++i) // O(N)
            vp.push_back({nums[i], i});
        sort(begin(vp), end(vp)); // O(NlogN)
        long long ans{};
        unordered_set<int> visited;
        for(int i = 0; i < nums.size(); ++i) { //O(N)
            int v = vp[i].first;
            int idx = vp[i].second;
            if(!visited.count(idx)) {
                ans += v;
                visited.insert(min(sz - 1, idx + 1));
                visited.insert(max(0, idx - 1));
            }
        }
        return ans;
    }
};
/*  參考 : https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/solutions/3312018/index-array/
 * 
 *  想法一樣只是改用index array
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    long long findScore(vector<int>& n) {
        long long score = 0, sz = n.size();
        vector<int> id(sz);
        iota(begin(id), end(id), 0);
        stable_sort(begin(id), end(id), [&](int i, int j){ return n[i] < n[j]; });
        for (int i : id)
            if (n[i]) { // 因為 1 <= nums[i]
                score += n[i];
                n[i] = n[min((int)sz - 1, i + 1)] = n[max(0, i - 1)] = 0;
            }
        return score;
    }
};
