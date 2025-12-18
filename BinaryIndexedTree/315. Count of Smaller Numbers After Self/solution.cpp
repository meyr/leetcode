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
    vector<int> countSmaller(vector<int>& nums) {
        int sz = 2e4 + 2;
        BIT bit(sz);
        vector<int> ans(nums.size());
        for(int i = nums.size() - 1; i >= 0; --i) { // 找出比目前的數字nums[i]還小的數字有多少個
            ans[i] = bit.query(nums[i] + 1e4);
            bit.update(nums[i] + 1e4 + 1, 1);
        }
        return ans;
    }
};
