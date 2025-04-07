/*  一開始使用0/1 pack解法 就是選擇要+或是- 最後檢查是否為0
 */
class Solution {
    vector<unordered_map<int, int>> mem;
    int sz;
    int helper(vector<int>& nums, int idx, int sum) {
        if(idx == sz) return sum == 0;
        else if(mem[idx].count(sum)) return mem[idx][sum];
        else return mem[idx][sum] = helper(nums, idx + 1, sum + nums[idx]) ||
                                    helper(nums, idx + 1, sum - nums[idx]);
    }
public:
    bool canPartition(vector<int>& nums) {
        int total = accumulate(begin(nums), end(nums), 0);
        if(total % 2 == 1) return false;
        sz = nums.size();
        mem.resize(sz, unordered_map<int, int>());
        return helper(nums, 0, 0);
    }
};
/*  因為分成兩個subset所以總和一定是total / 2
 *  只要變成選擇和不選即可
 */
class Solution {
    bool helper(vector<int>& nums, int idx, int sum) {
        if(sum < 0) return false;
        else if(~mem[idx][sum]) return mem[idx][sum];
        else if(idx == nums.size()) return mem[idx][sum] = false;
        else return mem[idx][sum] = helper(nums, idx + 1, sum) || helper(nums, idx + 1, sum - nums[idx]);   // 選擇或是不選擇
    }
    vector<vector<int>> mem;
    int sz;
public:
    bool canPartition(vector<int>& nums) {
        int total = accumulate(begin(nums), end(nums), 0);
        sz = nums.size();
        if(total % 2) return false;
        int target = total / 2;
        mem.resize(sz + 1, vector<int>(target + 1, -1));
        for(int i = 0; i < sz + 1; ++i)
            mem[i][0] = 1;
        return helper(nums, 0, target);
    }
};
/*  參考chatgpt的解釋
 *  因為目的是選擇nums來達到 target = total / 2
 *  所以只要確定subset的組合可以達到target即可
 *
 *  ex: 1, 5, 11, 5
 *  init   [0]
 *  n = 1  [0][1]
 *  n = 5  [0][1][5][6]
 *  n = 11 [0][1][5][6][11][12][16][17]
 *  n = 5  [0][1][5][6][11][12][16][17][5][6][10][11][16][17][21][22] --> [0][1][5][6][10][11][12][16][17][21][22]
 *
 *  dp |= dp << n
 */ 
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total{};
        bitset<10001> bs;
        bs[0] = 1;
        for(auto& n : nums) {
            total += n;
            bs |= bs << n;
        }
        return total % 2 == 0 && bs[total / 2];
    }
};
