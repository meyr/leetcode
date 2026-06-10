/*  參考:https://leetcode.com/problems/maximum-total-subarray-value-ii/solutions/8314399/maximum-total-subarray-value-ii-by-leetc-9d1c/
 *  參考AI的解釋
 *
 *  考慮一個數列
 *  nums = [4,2,5,1], 假設固定left = 0, 則subarray為 [4], [4, 2], [4, 2, 5], [4, 2, 5, 1]
 *                    其中最大值為 4, 4, 5, 5 因為納入的數字越多 最大值只會越來越大 所以是遞增的趨勢
 *                    其中最小值為 4, 2, 2, 1 因為納入的數字越多 最小值只會越來越小 所以是遞減的趨勢
 *                    所以最大值 - 最小值 0, 2, 3, 4 只會越來越大
 *
 *  Greedy point : 因為題目要求k個subarray使得sum(maxvalue - minvalue)為最大值 所以我們只需要從最大長度的subarray開始取
 *                 也就是 nums[0, n - 1], nums[1, n - 1] ... nums[n - 1, n - 1], 放入maxheap來比較
 *                 當取出一個就把那一列的下下一個放進去, 例如取了nums[0, n - 1] 就把 nums[0, n - 2]放入 必須確定right >= left
 *
 *  range maximun query(RMQ) 問題可以使用sparse table或是segment tree
 *  因為這邊不會改變nums的內容 所以使用sparse table
 *
 *  time  : O(NlogN + N + KlogN) = O(NlogN + KlogN) = O((N+K)logN)
 *  space : O(NlogN + N) = O(NlogN)
 */
template<typename T>
class SparseTable {
private:
    using compartor = function<T(T&, T&)>;
    vector<vector<T>> st;       // O(NlogN)
    compartor op;
public:
    SparseTable(const vector<int>& nums, const compartor& func) {
        auto n = nums.size();
        if (n == 0) return;
        op = move(func);
        auto logn = sizeof(T) * 8 - __builtin_clz(n);
        st.resize(n, vector<T>(logn));

        for (auto i = 0; i < n; i++)    // O(N)
            st[i][0] = nums[i];

        for (auto j = 1; j < logn; j++) {   // O(NlogN)
            for (auto i = 0; i + (1 << j) <= n; i++) {
                st[i][j] = op(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(int l, int r) { // O(1)
        auto j = (sizeof(T) * 8 - 1) - __builtin_clz(r - l + 1);
        return op(st[l][j], st[r - (1 << j) + 1][j]);
    }
};

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        SparseTable<int> stMax(nums, [](int& a, int& b)-> int {
            return max(a, b);
        });
        SparseTable<int> stMin(nums, [](int& a, int& b)-> int {
            return min(a, b);
        });
        int n = nums.size();
        priority_queue<tuple<int, int, int>> pq;
        for (int l = 0; l < n; l++) // O(N)
            pq.emplace(stMax.query(l, n - 1) - stMin.query(l, n - 1), l, n - 1);

        long long ans = 0;
        while (k--) { // O(KlogN)
            auto [val, l, r] = pq.top(); pq.pop();
            ans += val;
            if (r > l)  // 放入maxheap O(logN)
                pq.emplace(stMax.query(l, r - 1) - stMin.query(l, r - 1), l, r - 1);
        }
        return ans;
    }
};
