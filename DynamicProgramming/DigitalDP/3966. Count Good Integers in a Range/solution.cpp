class Solution {
    int k;
    long long dp[16][10][2][2];

    long long helper(string_view sv, int prev, int idx, int is_tight, int is_leading_zero) {
        if (idx == sv.size()) return !is_leading_zero; // 前面都不是0才需要計算

        if (dp[idx][prev][is_tight][is_leading_zero] != -1)
            return dp[idx][prev][is_tight][is_leading_zero];

        int limit = is_tight ? sv[idx] - '0' : 9;
        long long ans = 0;

        for (int d = 0; d <= limit; ++d) {
            bool next_leading_zero = is_leading_zero && (d == 0);
            bool next_tight = is_tight && (d == limit);

            if (is_leading_zero)    // 如果前面都是0 沒有前一個digit可以比較 所以任何數值都可以
                ans += helper(sv, d, idx + 1, next_tight, next_leading_zero);
            else {                  // 前面有數字 就必須滿足 abs(prev - d) <= k
                if (abs(prev - d) <= k)
                    ans += helper(sv, d, idx + 1, next_tight, next_leading_zero);
            }
        }

        return dp[idx][prev][is_tight][is_leading_zero] = ans;
    }

    long long solve(long long num) {
        if (num < 0) return 0;
        string s = to_string(num);
        memset(dp, -1, sizeof(dp));
        return helper(s, 0, 0, 1, 1);
    }

public:
    long long goodIntegers(long long l, long long r, int k) {
        this->k = k;
        return solve(r) - solve(l - 1);
    }
};
