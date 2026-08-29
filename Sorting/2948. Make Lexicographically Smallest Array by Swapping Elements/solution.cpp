/*  參考:
 *  https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/solutions/4330378/union-find-vs-sort-by-votrubac-sc77/
 *
 *  只要數值相差limit就可以連接起來 因為要找Lexicographically Smallest 
 *  所以先對nums排序 只要就可以找出那些數字為一群 根據這些數字的index依序從小到大放入
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    void populateResult(vector<int> &res, vector<int> &ids, vector<int> &vals) {
        sort(begin(ids), end(ids));
        for (int j = 0; j < ids.size(); ++j)
            res[ids[j]] = vals[j];
    }
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        vector<int> ds(nums.size(), -1), ids(nums.size()), res(nums.size()); 
        iota(begin(ids), end(ids), 0);  // O(N)
        sort(begin(ids), end(ids), [&](int i, int j){ return nums[i] < nums[j]; }); // O(NlogN)
        vector<int> group_ids{ids[0]}, group_vals{nums[ids[0]]};
        for (int i = 1; i < nums.size(); ++i) {             // O(N)
            if (nums[ids[i]] - nums[ids[i - 1]] > limit) {
                populateResult(res, group_ids, group_vals);
                group_ids = group_vals = vector<int>();
            }
            group_ids.push_back(ids[i]);
            group_vals.push_back(nums[ids[i]]);
        }
        populateResult(res, group_ids, group_vals);
        return res;
    }
};
/*
 *      任兩個i, j如果abs(nums[i] - nums[j]) <= limit就可以交換
 *      __important__ 例如1, 3, 5, limit = 2, 1和3可以交換, 3和5可以交換，但是1和5不能交換
 *                    可是我們使用以下方法 [1, 3], 5 --> [3], 1, [5] --> 5, [1, 3] --> 5, 3, 1
 *                    最後結果也是達到1和我5交換，也就是一串排列過的數字只要相差limit之內都可以交換
 *                    所以我們先把數字分類 相同的group就可以交換 最後只要把group內的數字排序即可
 *
 */
class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int sz = nums.size();
        vector<int> idxs(sz);
        iota(begin(idxs), end(idxs), 0);
        sort(begin(idxs), end(idxs), [&](int a, int b){
            return nums[a] < nums[b];
        });
        int g{};
        unordered_map<int, vector<int>> groups;
        groups[g].push_back(idxs[0]);
        for(int i = 1; i < sz; ++i) {   // 統計所有的groups
            if(nums[idxs[i]] - nums[groups[g].back()] <= limit)
                groups[g].push_back(idxs[i]);
            else groups[++g].push_back(idxs[i]);
        }
        for(auto& ref : groups) {       // 針對每個group排序
            if(ref.second.size() == 1) continue;
            auto pos = ref.second;      // ref.second 從小到大的排序
            sort(begin(pos), end(pos)); // 排列過的pos 在groups中出現的順序
            vector<int> vals;
            for(auto& p : ref.second) vals.push_back(nums[p]);  // 把從小到大的數值備份出來
            for(int i = 0; i < vals.size(); ++i)                // 針對這個group的index把數值從小到大填入
                nums[pos[i]] = vals[i];
        }
        return nums;
    }
};
