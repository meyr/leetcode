/*
 *  Digit DP 就是填空格遊戲 並且記錄此路徑有那些結果是符合的
 *
 *  __important__ 決定mem中的idx和count的大小
 *                idx是由 str的大小決定
 *                count是由一個答案中最多可能來決定
 *                     因為n <= 1e9 最多是 11111111 8個1 9個1就會超過1e9
 */
class Solution {
    vector<vector<int>> mem;
    int helper(string_view str, int idx, int count, bool is_tight) {
        if(idx == str.size()) return count;                             // 到達最後位數 返回這個路徑的count
        if(!is_tight && ~mem[idx][count]) return mem[idx][count];       // __important__ 只有不受限才可以參考儲存結果 有受限的情況不能取不受限的結果
        int ans{};
        int limit = is_tight ? str[idx] - '0' : 9;
        for(int d = 0; d <= limit; ++d)
            ans += helper(str, idx + 1, count + (d == 1), is_tight && d == limit);  // __important__ 因為我們使用count來記錄 所以不能使用 +=
        return mem[idx][count] = ans;
    }
public:
    int countDigitOne(int n) {
        mem.resize(10, vector<int>(9, -1));
        return helper(to_string(n), 0, 0, true);  // 第一次一定是 is_tight 一定是true, 例如 n = 234, idx == 0 只能填入 0, 1, 2
    }
};
