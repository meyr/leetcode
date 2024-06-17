/*
 *  統計某個區間的peak數量 很明顯就是binary indexed tree的題目 但是需要注意的點很多
 *
 *  time  : update O(logN), query O(logN), N : length of nums
 *  space : O(N)
 */

class BIT{
    vector<int> bit;
    int sz;
public:
    BIT(int _sz) : sz(_sz + 1), bit(_sz + 1){}
    void update(int idx, int val) {
        ++idx;
        while(idx < sz) {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }
    int getSum(int idx) {
        ++idx;
        int rtn{};
        while(idx > 0) {
            rtn += bit[idx];
            idx -= idx & -idx;
        }
        return rtn;
    }
};
class Solution {
    int isPeak(vector<int>& nums, int idx) {
        if(idx == 0 || idx == nums.size() - 1) return 0;
        else return (nums[idx] > nums[idx + 1]) && (nums[idx] > nums[idx - 1]);
    }
public:
    vector<int> countOfPeaks(vector<int>& nums, vector<vector<int>>& queries) {
        int sz = nums.size();
        vector<int> peak(sz); // 因為BIT.update(idx, val) 中的val是差值 所以必須儲存之前的狀態
        BIT bit(sz);
        for(int i = 1;i < sz; ++i) {
            peak[i] = isPeak(nums, i);
            if(peak[i])
                bit.update(i, 1);
        }
        vector<int> ans;
        for(auto& q : queries) {
            if(q[0] == 1) { // query
                if(q[2] - q[1] + 1 < 3) ans.push_back(0); // subarray長度小於3 就不用比了
                else {
                    int left = bit.getSum(q[1]);
                    int right = bit.getSum(q[2] - 1); // subarray最前面和最後面不會是peak
                    ans.push_back(right - left);
                }
            } else {
                nums[q[1]] = q[2];
                for(int i = max(1, q[1] - 1); i <= min(q[1] + 1, sz - 2); ++i) { // 必須注意是否會超過peak的邊界
                    int prev = peak[i];
                    peak[i] = isPeak(nums, i);
                    if(peak[i] != prev) // 如果peak前後不一樣 更新BIT
                        bit.update(i, peak[i] - prev);
                }
            }
        }
        return ans;
    }
};
