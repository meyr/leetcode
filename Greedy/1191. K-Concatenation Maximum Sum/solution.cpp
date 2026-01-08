/*
            [a, b, c, d, e, f...z]

case 1:         |-----------|                            internal
case 2:               |----------|--------|             prefix + suffix
case 3:               |----------|-------------|*k-1    suffix + (total)*(k-1)
case 4:     |---------------------|                     total * k
case 5:                |----------||-----------|*k-2|---------| suffix + (total)*(k - 2) + prefix

time  : O(N + N) = O(N)
space : O(1)
*/

class Solution {
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        long long maxinter{}, prefix{INT_MIN}, cur{}, minv{};
        for(auto& n : arr) {
            cur += n;
            prefix = max(prefix, cur);
            maxinter = max(maxinter, cur - minv);
            minv = min(minv, cur);
        }
        long long total = cur, suffix{INT_MIN};
        cur = 0;
        for(int i = arr.size() - 1; i >= 0; --i) {
            cur += arr[i];
            suffix = max(suffix, cur);
        }
        if(k == 1) return maxinter;
        long long rtn = max({
            maxinter,
            suffix + prefix,
            suffix + total * (k - 1),
            total * k,
            suffix + total * (k - 2) + prefix
        });
        return rtn % (int)(1e9 + 7);
    }
};
