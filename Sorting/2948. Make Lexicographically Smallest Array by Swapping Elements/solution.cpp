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
