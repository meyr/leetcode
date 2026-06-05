/*  參考AI解答和加上自己的改良 比較好理解 但是time complexity比較糟
 */
class Solution {
    using ll = long long;
    using vll = vector<ll>;
    using vvll = vector<vll>;
    using vvvll = vector<vvll>;
    using vvvvll = vector<vvvll>;
    ll helper(vvvvll& mem, string_view str, int idx, int count, int prev2, int prev1, bool is_tight, bool is_leading_zero) {
        if(idx == str.size()) return count;
        else if(!is_tight && !is_leading_zero && ~mem[idx][count][prev2][prev1]) // 只有在!is_tight && !is_leading_zero才取結果
            return mem[idx][count][prev2][prev1];
        int limit = is_tight ? str[idx] - '0' : 9;
        ll ans{};
        for(int d = 0; d <= limit; ++d) {
            int next_count = count;
            if(idx >= 2 && !is_leading_zero && prev2 != 10 && prev1 != 10) {
                next_count += prev1 > prev2 && prev1 > d;
                next_count += prev1 < prev2 && prev1 < d;
            }
            bool next_tight = is_tight && d == limit;
            bool next_leading_zero = is_leading_zero && d == 0; // __important__ 確定是否前面都是0
            int next_prev2 = next_leading_zero ? 10 : prev1;    //               如果前面都是0, 就不動prev2
            int next_prev1 = next_leading_zero ? 10 : d;        //               如果前面都是0, 就不動prev1
            ans += helper(mem, str, idx + 1, next_count, next_prev2, next_prev1, next_tight, next_leading_zero);
        }
        if(!is_tight && !is_leading_zero)                       // 只有在!is_tight && !is_leading_zero才紀錄
            mem[idx][count][prev2][prev1] = ans;
        return ans;
    }
    ll solve(ll num) {
        if(num < 100) return 0;
        string str = to_string(num);
        int sz = str.size();
        vvvvll mem(sz + 1, vvvll(15, vvll(11, vll(11, -1))));
        return helper(mem, to_string(num), 0, 0, 10, 10, true, true);
    }
public:
    long long totalWaviness(long long num1, long long num2) {
        return solve(num2) - solve(num1 - 1);
    }
};
