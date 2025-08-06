/*  ref : https://leetcode.com/problems/fruits-into-baskets-iii/solutions/7030238/fruits-into-baskets-iii-by-leetcode-f9fy/ 
 * 
 *  使用segment tree建立maximum value query 就是找區間最大值
 *  策略是
 *  1. 先找vector左半邊 如果有找到繼續
 *  2. 如果沒找到就找右半邊
 */
class Solution {
    template<typename T>
    class ST{  // maximum segment tree
        vector<T> st, nums;
        const int sz;
        const function<T(T, T)> f;
        void build(int node, int left, int right) {
            if(left == right)
                st[node] = nums[left];
            else {
                int mid = (left + right) / 2;
                build(2 * node,        left, mid);
                build(2 * node + 1, mid + 1, right);
                st[node] = f(st[2 * node], st[2 * node + 1]);
            }
        }
        void _update(int node, int left, int right, const int idx, const T val) {
            if(idx < left or idx > right) return;
            else if(left == right) {
                st[node] = val;
                nums[idx] = val;
            } else {
                int mid = (left + right) / 2;
                _update(2 * node,        left,   mid, idx, val);
                _update(2 * node + 1, mid + 1, right, idx, val);
                st[node] = f(st[2 * node], st[2 * node + 1]);
            }
        }
        T _query(int node, int left, int right, const int qleft, const int qright) const {
            if(qright < left or qleft > right) return 0; //out of range
            else if(qleft <= left and qright >= right) return st[node]; // include this range
            else {
                int mid = (left + right) / 2;
                return f(_query(2 * node,        left,   mid, qleft, qright),
                         _query(2 * node + 1, mid + 1, right, qleft, qright));
            }
        }
    public:
        ST(vector<T>& vec, const function<T(T, T)>& _f) : nums(vec), f(_f), sz(vec.size()) {
            st.resize(sz * 4);
            build(1, 0, sz -1);
        }
        void update(int idx, T val) {
            return _update(1, 0, sz - 1, idx, val);
        }
        T query(int left, int right) const {
            return _query(1, 0, sz - 1, left, right);
        }
        T getMaxValue() const {
            return st[1];
        }
    };
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int ans{};
        ST<int> maxTree{baskets, [](auto a, auto b)->int{
            return max(a, b);
        }};
        for (int i = 0; i < fruits.size(); i++) {
            int left = 0, right = baskets.size() - 1, res = -1;
            if(maxTree.getMaxValue() < fruits[i]) {
                ans++;
                continue;
            }
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (maxTree.query(0, mid) >= fruits[i]) {   // 有在左半邊嗎? 如果有繼續往左半邊找
                    res = mid;                              // 有找到, 紀錄找到的index
                    right = mid - 1;
                } else {                                    // 不然就是在右半邊
                    left = mid + 1;
                }
            }
            if (res != -1 && baskets[res] >= fruits[i])
                maxTree.update(res, 0);
            else
                ans++;

        }
        return ans;
    }
};
