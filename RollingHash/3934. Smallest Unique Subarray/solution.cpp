/*
 * len   : 1, 2, 3, [4], 5
 * check : x, x, x,  o, o
 *
 * 如果len == 4有Unique Subarray, 那len > 4也會有unique subarray
 * 因為 [a, b, c, d] 為unique subarray
 * 則   [a, b, c, d, e] 不管e怎麼變 [a, b, c, d]是unique subarray則 [a, b, c, d, e]也是unique subarray
 *
 *
 *  找unique subarray 使用rolling hash
 *
 *  [a0, a1, a2, a3]   hash
 *  ---                = (0 * p) + a0 = a0
 *  -------            = (a0 * p) + a1 = a0*p + a1
 *  -----------        = (a0*p + a1)*p + a2 = a0*p*p + a1*p + a2
 *       ----------    = (h2 - a0*p*p) * p + a3 = a1*p*p + a2*p + a3
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
    bool check(const vector<int>& nums, int len) {
        int m = 1e9 + 7, p = 107, rtn{};
        long long hash{}, pk{1};
        unordered_map<long long, int> count;
        for(int i = 0; i < nums.size(); ++i) {
            hash = ((hash * p) + nums[i] ) % m;
            if(i < len - 1) pk = (p * pk) % m;
            if(i >= len - 1) {
                count[hash]++;
                hash = (hash - (nums[i - len + 1] * pk) % m + m) % m; // __important__ 因為hash - nums[i-len+1] 可能為負 所以取mod之後還要加m
            }                                                         //                                        可能為正     取mod之後再加m 有可能大於m 所以在取一次mod
        }
        bool rtn{false};
        for(auto& ref : count) {
            if(ref.second == 1)
                rtn = true;
        }
        return rtn;
    }
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int left = 1, right = nums.size();
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(check(nums, mid)) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
/*      2026/11/25 daily challenge
 *      還是不懂為什麼可以用binary search 所以重新思考了一次
 *      把可能的結果都列一次 這樣才確信當length = 3有unique subarray則length = 4也會有
 *
 *
    why binary search?
    如果len可以找出unique subarray
    則 len + 1也可以找到?
    [a, b, c] 是length = len 的unique subarray

    [a, b, c, d, e, f]  len = 3 subarray --> [a, b, c][b, c, d][c, d, e][d, e, f]
                        len = 4 subarray -->     |         \         \
                                                \|/         \         \
                                             [a, b, c, d]    \/        \
                                                       [b, c, d, e]     \/
                                                                  [c, d, e, f]

    如果unique subarray是 [d, e, f] 因為為了拚len + 1所以改成往前取一個

    [a, b, c, d, e, f]  len = 3 subarray --> [a, b, c][b, c, d][c, d, e][d, e, f]
                        len = 4 subarray -->             /        /         |
                                                        /        /         \|/
                                                       /       \/     [c, d, e, f]
                                                     \/     [b, c, d, e]
                                                [a, b, c, d]

    如果[d, e, f]是unique subarray則多拚一個c變成[c, d, e, f]也是unique subarray

    所以只要len 有unique subarray則len + 1也一定會有unique subarray --> 使用binary search
    len  : 1, 2, 3, 4, 5
    check: x  x  o  o  o
              [   ]
 */
class Solution {
    // 使用check()會MLE 必須修改成rolling hash 這樣TC才會是O(N)
    bool check(vector<int>& nums, int len) {
        map<vector<int>, int> mp;
        for(int i = 0; i + len <= nums.size(); ++i)
            mp[vector<int>(begin(nums) + i, begin(nums) + i + len)]++;
        for(auto& ref : mp)
            if(ref.second == 1)
                return true;
        return false;
    }
    // rolling hash
    // [a, b, c]       --> a*p^2 + b * p^1 + c * p^0                     = val1
    //    [b, c, d]    -->         b * p^2 + c * p^1 + d * p^0           = (val1 - a*p^2) * p + d  = val2
    //        [c, d, e]-->                   c * p^2 + d * p^1 + e * p^0 = (val2 - b*p^2) * p + e  = val3
    bool check2(vector<int>& nums, int len) {
        static const int mod = 1e9 + 7;
        static const int p = 107;
        unordered_map<long long, int> count;
        long long val{};
        long long vp{1};
        for(int i = 0; i < nums.size(); ++i) {
            val = ((val * p) + nums[i]) % mod;
            if(i < len - 1) vp = (vp * p) % mod;
            if(i >= len - 1) {
                count[val]++;
                val = (val - (nums[i - len + 1] * vp) % mod + mod) % mod;
            }
        }
        for(auto& ref : count)
            if(ref.second == 1)
                return true;
        return false;
    }
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int left = 1, right = nums.size();
        while(left < right) {
            int mid = (left + right) / 2;
            if(check2(nums, mid))  right = mid;
            else left = mid + 1;
        }
        return left;
    }
    // time  : O(NlogN)
    // space : O(NlogN)
};
