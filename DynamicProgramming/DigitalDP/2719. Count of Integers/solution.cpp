/*  參考chatgpt解答 
 *
 *
 */
class Solution {
public:
    static constexpr int MOD = 1e9 + 7;
    int min_sum, max_sum;
    vector<vector<vector<int>>> memo;

    // 核心：digit dp
    int dfs(int pos, int sum, bool tight, const string &num) {
        if (sum > max_sum) return 0; // 超出最大數字和直接剪枝
        else if (pos == num.size()) return sum >= min_sum && sum <= max_sum;
        else if (~memo[pos][sum][tight]) return memo[pos][sum][tight];
        else {
            int res = 0;
            // __important__ 表示前一個數字和num[pos - 1]一樣 則目前的數字不能超過 
            int limit = tight ? (num[idx] - '0') : 9;

            for (int d = 0; d <= limit; ++d) 
                res = (res + dfs(num, idx + 1, sum + d, tight && (d == limit))) % MOD;

            return res;
        }
    }

    int count(string num) {
        int n = num.size();
        memo.assign(n, vector<vector<int>>(500, vector<int>(2, -1)));  // 每次都要reset memo才不會被上次結果影響
        return dfs(0, 0, true, num);
    }

    int count(string num1, string num2, int min_sum, int max_sum) {
        this->min_sum = min_sum;
        this->max_sum = max_sum;

        // 先對 num1 - 1
        string num1_minus_1 = minusOne(num1);   // 減1是因為 num1 <= x <= num2 包括 x == num1

        int count2 = count(num2);
        int count1 = count(num1_minus_1);

        int ans = (count2 - count1 + MOD) % MOD;
        return ans;
    }

private:
    // 計算字串數字減一             __important__ 使用字串來減1 而不是轉成數字減1再轉回來
    //                                                          因為數字範圍為 1 <= num1 <= num2 <= pow(10, 22)
    //                                                          pow(10, 22)無法使用long long來儲存
    string minusOne(string num) {
        int n = num.size();
        int i = n - 1;                      // i為最低位元的index    
        while (i >= 0 && num[i] == '0') {   // 遇到'0'就變成'9'並且往前
            num[i] = '9';
            i--;
        }
        if (i >= 0) num[i]--;                   // 最後i停在的位置必須減1
        // 去除開頭 0
        if (num[0] == '0') num = num.substr(1); // 去除開頭的0
        return num;
    }
};

