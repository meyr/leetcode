/*
 *  time  : O(N + N) = O(N)
 *  space : O(P)
 */
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int target = accumulate(begin(nums), end(nums), 0LL) % p;
        if(target == 0) return 0;
        int sz = nums.size();
        int ans = sz;
        unordered_map<int, int> um{{0, -1}};
        for(int i = 0, cur = 0; i < nums.size(); ++i) {
            cur = (cur + nums[i]) % p;
            int need = (cur - target + p) % p;      // __important__ 找出需要的prefix sum
            if(um.count(need)) ans = min(ans, i - um[need]);
            um[cur] = i;
        }
        return ans == sz ? -1 : ans;
    }
};
