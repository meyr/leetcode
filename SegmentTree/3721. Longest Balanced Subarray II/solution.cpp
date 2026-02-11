/* 因為看不懂線上solution
 * 所以參考gemini pro的解法
 *
 * 對segment tree還真的蠻苦手的
 * 這題的重點是統計distinct even/odd number 也就是相同的subarray中相同的數字只算一次
 *
 *  奇數 +1, 偶數 -1
 * 如果不考慮distinct, 只要是even就是-1, odd就是+1, 總和是0 就是balanced subarray
 * 假設right在index = 6, 所以有[0, 6][1, 6][2, 6][3, 6][4, 6][5, 6][6, 6] 七個以right為結尾的subarray
 *
 *                         right
 * idx  : 0, 1, 2, 3, 4, 5, 6
 * nums : 3, 5, 4, 3, 1, 2, 6
 * pfs  : 1  0 -1 0 -1 -2 -1   如果從right開始累加+/-1到left, 最左邊的0就是最長的balanced subarray, 這是不考慮重複數字的狀況
 *           |--------------|
 *
 * ** 如果考慮重複數字的情況 **
 *
 *                         right
 * idx  : 0, 1, 2, 3, 4, 5, 6
 * nums : 3, 5, 4, 3, 1, 2, 6
 * pfs  : 0  0  -1 0 -1 -2 -1
 *           |--------------|   因為3重複, 3影響的範圍是[prev_pos + 1, right] 也就是[1, 6][2, 6][3, 6][4, 6][5, 6],[6, 6] 這六個個subarray
 *              |-----------|              必須把[prev_pos, right] 都-1 --> 區間的加減最適合使用segment tree with lazy
 *                 |--------|
 *                    |-----|
 *                       |--|
 *                         ||
 *
 * 所以實際的prefix sum會像這樣
 * nums : 3, 5, 4, 3, 1, 2, 6
 * pfs  : 1
 *        2  1
 *        1  0 -1                  <-- [1, 2] is balanced subarray
 *        1  1  0  1               <-- idx = 3的時候 idx = 0 沒有更新
 *        2  2  1  2  1
 *        1  1  0  1  0 -1         <-- [2, 5]
 *        0  0 -1  0 -1 -2 -1      <-- [0, 6]
 *
 */
struct Node {                   // segment tree的設計 紀錄區間最大最小值
    int min_val;
    int max_val;
    int lazy;                   // lazy為區間update的時候必須向下推的更新值
} tree[400005]; // 4 * N

class Solution {
public:
    int n;

    // 初始化線段樹 (全部為 0)
    void build(int node, int start, int end) {
        tree[node] = {0, 0, 0};
        if (start == end) return;
        int mid = (start + end) / 2;
        build(2 * node, start, mid);
        build(2 * node + 1, mid + 1, end);
    }

    // 下推 Lazy 標記
    void push(int node) {                                   // 全部的區間都加上某個值那麼max_val, min_val也會加上更新值
        if (tree[node].lazy != 0) {
            tree[2 * node].lazy += tree[node].lazy;
            tree[2 * node].min_val += tree[node].lazy;
            tree[2 * node].max_val += tree[node].lazy;

            tree[2 * node + 1].lazy += tree[node].lazy;
            tree[2 * node + 1].min_val += tree[node].lazy;
            tree[2 * node + 1].max_val += tree[node].lazy;

            tree[node].lazy = 0;
        }
    }

    // 區間更新
    void update(int node, int start, int end, int l, int r, int val) {
        if (r < start || end < l) return;
        if (l <= start && end <= r) {                                   // __要更新的區域包含目前的區域__ 只更新lazy, max_val和min_val
            tree[node].lazy += val;
            tree[node].min_val += val;
            tree[node].max_val += val;
            return;
        }
        push(node);
        int mid = (start + end) / 2;
        update(2 * node, start, mid, l, r, val);
        update(2 * node + 1, mid + 1, end, l, r, val);
        tree[node].min_val = min(tree[2 * node].min_val, tree[2 * node + 1].min_val);
        tree[node].max_val = max(tree[2 * node].max_val, tree[2 * node + 1].max_val);
    }

    // 查詢最左邊的 0 的位置
    // 利用性質：如果區間 min <= 0 <= max，則 0 一定存在
    int query_first_zero(int node, int start, int end) {
        // 如果 0 不在這個區間的值域內，直接剪枝
        if (tree[node].min_val > 0 || tree[node].max_val < 0) return -1;    //__imporant__ 正常來說這個區域有0 表示 min_val <= 0 <= max_val
                                                                            //             如果沒有0則    0 < min_val <= max_val   or  min_val <= max_val < 0
        if (start == end) {
            return (tree[node].min_val == 0) ? start : -1;
        }

        push(node);
        int mid = (start + end) / 2;

        // __important__ 優先找左邊 因為我們要最長的subarray 如果找到就返回
        int res = query_first_zero(2 * node, start, mid);
        if (res != -1) return res;

        // 左邊找不到找右邊
        return query_first_zero(2 * node + 1, mid + 1, end);
    }

    int longestBalanced(vector<int>& nums) {
        n = nums.size();
        build(1, 0, n - 1); // 線段樹範圍涵蓋所有可能的 left 位置

        unordered_map<int, int> last_pos;
        int max_len = 0;

        for (int right = 0; right < n; ++right) {
            int val = nums[right];
            int weight = (val % 2 != 0) ? 1 : -1; // 奇數 +1, 偶數 -1

            // 找出上一次該數字出現的位置，預設為 -1
            int prev = last_pos.count(val) ? last_pos[val] : -1;

            // 更新區間 [prev + 1, right]
            // 這個區間內的 left，都會把 nums[right] 視為新的不同元素
            update(1, 0, n - 1, prev + 1, right, weight);

            // 記錄當前位置
            last_pos[val] = right;

            // 查詢線段樹中，數值為 0 的最左側索引 left
            int left = query_first_zero(1, 0, n - 1);

            if (left != -1) {
                // 如果找到合法的 left，且 left <= right，計算長度
                if (left <= right) {
                    max_len = max(max_len, right - left + 1);
                }
            }
        }

        return max_len;
    }
};
