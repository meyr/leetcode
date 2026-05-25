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
