/*  這邊不使用count因為 只要可以走到最後都是一個答案
 *
 *  紀錄is_leading_zero 因為當is_leading_zero的時候d可以不受digit的限制 可以為0 表示不選的意思
 *
 *  time  : O(N*2*2) = O(N), N : digit sz  of n
 *  space : O(N*2*2) = O(N)
 */
class Solution {
    vector<vector<vector<int>>> mem;
    int helper(const unordered_set<int>& digits, string_view str, int idx, bool is_tight, bool is_leading_zero) {
        if(idx == str.size()) return !is_leading_zero;
        if(!is_tight && ~mem[idx][is_tight][is_leading_zero]) return mem[idx][is_tight][is_leading_zero];
        int limit = is_tight ? str[idx] - '0' : '9';
        int ans{};
        for(int d = 0; d <= limit; ++d) {
            if((is_leading_zero && d == 0) || digits.count(d)) {
                ans += helper(digits, str, idx + 1, is_tight && d == limit, is_leading_zero && d == 0);
            }
        }
        return mem[idx][is_tight][is_leading_zero] = ans;
    }
public:
    int atMostNGivenDigitSet(vector<string>& digits, int n) {
        unordered_set<int> us;
        for(const auto& str : digits)
            us.insert(str[0] - '0');
        mem.resize(10, vector<vector<int>>(2, vector<int>(2, -1)));
        return helper(us, to_string(n), 0, true, true);
    }
};
