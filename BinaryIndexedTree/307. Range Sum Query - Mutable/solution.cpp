/*  標準的binary index tree或是segment tree題目
 *  因為是range sum使用BIT來寫比較簡單
 */
class BIT{
    int sz;
    vector<int> bit;
    vector<int> orig;
    void _update(int idx, int diff) {
        idx++; // transfer to BIT index
        while(idx < sz) {
            bit[idx] += diff;
            idx += idx & -idx;
        }
    }
    int _getSum(int idx) {
        idx++;
        int rtn{};
        while(idx > 0) {
            rtn += bit[idx];
            idx -= idx & -idx;
        }
        return rtn;
    }
public:
    BIT(vector<int>& nums) : sz(nums.size() + 1), bit(sz), orig(begin(nums), end(nums)) {
        for(int i = 0; i < nums.size(); ++i)
            _update(i, nums[i]);
    }

    void update(int idx, int val) {
        int diff = val - orig[idx];
        orig[idx] = val;
        _update(idx, diff);
    }

    int rangeSum(int left, int right) {
        return _getSum(right) - _getSum(left - 1);
    }
};

class NumArray {
    BIT bit;
public:
    NumArray(vector<int>& nums) : bit(nums) {}
    void update(int index, int val) {
        bit.update(index, val);
    }
    int sumRange(int left, int right) {
        return bit.rangeSum(left, right);
    }
};
