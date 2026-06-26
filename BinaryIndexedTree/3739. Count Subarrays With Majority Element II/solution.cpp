/*  參考hint 把數字化成+1(target), -1(non target) 然後累加 當sum >= 1的時候就是subarray中majority element 多於一半以上
 *
 *  ex:
 *       1,  2,  2
 *      -1, +1, +1
 * sum  -1,  0,  1   --> pfs = 1,  pfs - x >= 1
 *                                 pfs - 1 >= x
 *                                 x <= pfs - 1   <-- 必須找出x小於等於 pfs - 1
 *
 * time  : O(N^2)  --> 因為N = 1e5 所以TLE
 * space : O(N)
 */
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        map<int, int> mp{{0, 1}};   // 使用map來記錄
        long long ans{};
        for(int i = 0, pfs = 0; i < nums.size(); ++i) {
            pfs += nums[i] == target ? 1 : -1;
            auto it = mp.begin();                               // 從最小開始
            while(it != mp.end() && it->first <= pfs - 1) {     // 只要滿足 x <= pfs - 1 就加入ans
                ans += it->second;
                it++;
            }
            mp[pfs]++;                                          // 紀錄目前的pfs
        }
        return ans;
    }
};
/*
 * 因為重點是找出小於等於pfs - 1的所有值相加 所以使用Binary index tree
 *
 * time  : O(NlogN)
 * space : O(N)
 */
class BIT{
    int n;
    vector<int> tree;
public:
    BIT(int _n) : n(_n), tree(_n + 1){}
    void update(int idx, int val) {
        idx++;
        while(idx <= n) {
            tree[idx] += val;
            idx += idx & -idx;
        }
    }
    int query(int idx) {
        int sum{};
        idx++;
        while(idx > 0) {
            sum += tree[idx];
            idx -= idx & -idx;
        }
        return sum;
    }
};

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int sz = nums.size();
        BIT bit(sz * 2 + 1);    // 因為可能有負值 所以shift sz
        bit.update(sz, 1);      // 先放入[0] = 1
        long long ans{};
        for(int i = 0, pfs = 0; i < nums.size(); ++i) {
            pfs += nums[i] == target ? 1 : -1;
            ans += bit.query(pfs - 1 + sz);     // 取得[0, pfs - 1] 所有值的和
            bit.update(pfs + sz, 1);
        }
        return ans;
    }
};
/*  參考官方解答
 *
 *  BIT 的好處是可以update任意的index, 也可以query任意的index 但是缺點是time complexity 是O(longN)
 *  這題有個特色 下一個pfs只會和上一個差+1/-1
 *  也就是我們可以使用presum 來記錄比目前還小的pfs總和是多少, 因為presum每次只會往前或是往後一格
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        // represents the occurrence count of prefix sums -n, -(n-1), ..., 0, 1,
        // ..., n, with index offset by n.
        vector<int> pre(n * 2 + 1, 0);
        pre[n] = 1;
        int cnt = n;
        long long ans = 0, presum = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                presum += pre[cnt];
                ++cnt;
                ++pre[cnt];
            } else {
                --cnt;
                presum -= pre[cnt];
                ++pre[cnt];
            }
            ans += presum;
        }
        return ans;
    }
};
