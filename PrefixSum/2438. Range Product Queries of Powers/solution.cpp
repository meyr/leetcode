/*  數字n 分解成 power-2的和 其實就是對每個bit 最拆解
 *  power-2相乘就是exp相加 所以使用prefix sum
 *
 *
 *  time  : O(N + N + M) = O(N + M)
 *  space : O(N + M)
 *
 */
class Solution {
    int powmod(int base, int exp, int mod = 1e9 + 7) {
        if(exp == 0) return 1;
        else if(exp == 1) return base;
        else {
            long long rtn = powmod(base, exp / 2, mod);
            rtn = (rtn * rtn ) % mod;
            return exp % 2 ? (rtn * base) % mod : rtn;
        }
    }
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> power;
        int i = 0;
        while(n) {
            if(n & 1)
                power.push_back(i);
            i++;
            n >>= 1;
        }
        partial_sum(begin(power), end(power), begin(power));
        vector<int> ans;
        for(auto& q : queries) {
            int val = power[q[1]] - (q[0] > 0 ? power[q[0] - 1] : 0);
            ans.push_back(powmod(2, val));
        }
        return ans;
    }
};
/* 因為是range query可以使用 segment tree
 *
 */
template<typename T>
class ST{
    vector<T> st, nums;
    const int sz;
    int _rtn;
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
        if(qright < left or qleft > right) return _rtn; //out of range                          // __important__ : 因為是product所以必須回傳1 所以此value也改成傳入值
        else if(qleft <= left and qright >= right) return st[node]; // include this range
        else {
            int mid = (left + right) / 2;
            return f(_query(2 * node,        left,   mid, qleft, qright),
                     _query(2 * node + 1, mid + 1, right, qleft, qright));
        }
    }
public:
    ST(vector<T>& vec, const function<T(T, T)>& _f, int qrtn) : ST<T>(vec, _f) {
        _rtn = qrtn;
    }

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

class Solution {
public:
    vector<int> productQueries(int n, vector<vector<int>>& queries) {
        vector<int> power;
        int mod = 1e9 + 7;
        for(int i = 0; n; ++i, n >>= 1) {
            if(n & 1)
                power.push_back(pow(2, i));
        }

        ST<int> st(power, [](auto a, auto b){
            return ((long long)a * b) % (int)(1e9 + 7);
        }, 1);

        vector<int> ans;
        for(const auto& q : queries) {
            ans.push_back(st.query(q[0], q[1]));
        }
        return ans;
    }
};
