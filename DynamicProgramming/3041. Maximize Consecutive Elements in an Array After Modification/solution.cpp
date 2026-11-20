/*
	why dynamic programming?
	因為每增加一個element，可以根據之前的結果來得到

*/
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(begin(nums), end(nums)); //O(NlogN)
        unordered_map<int, int> m; //value, length
        int ans{1};
        for(auto& n : nums) { // O(N)
            if(m.count(n)) {
                m[n + 1] = max(m[n + 1], m[n] + 1);
                ans = max(ans, m[n + 1]);
            }
            if(m.count(n - 1)) {
                m[n] = max(m[n], m[n - 1] + 1);
                ans = max(ans, m[n]);
            }
            m[n] = max(m[n], 1);
            m[n + 1] = max(m[n + 1], 1);
        }
        return ans;
        // time : O(NlogN + N) = O(NlogN)
        // space : O(logN + N)
    }
};
/*
 *      2026/11/20 daily challenge
 *      參考官方解答
 */
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(begin(nums), end(nums));
        unordered_map<int, int> m; // value, length
        int ans{};
        for(auto& x : nums) {
            m[x + 1] = max(m[x + 1], m[x] + 1); // 當成是x + 1, 如果m[x]有值就繼續接下去
            m[x] = max(m[x], m[x - 1] + 1);     // 當成是x 如果m[x - 1]有值就繼續接下去   如果順序反過來 m[x + 1] 會拿到之前先放入的m[x] 一個num使用兩次
            ans = max({ans, m[x], m[x + 1]});
        }
        return ans;
    }
};
/*
    [1, 1, 1, 2, 5]
     *                  dp[1] = 1, dp[2] = 1    以1結尾或是以2結為的連續遞增序列只有1
                          |
                         \|/
        *               dp[2] = 2, dp[1] = 1(因為dp[0] = 0)
                        [1, 2]情況
            *           dp[2] = 2, dp[1] = 1   還是一樣
                          |           |
                         \|/         \|/
               *        dp[3] = 3, dp[2] = 2
                        [1, 2, 3]   [1, 2]
                  *     dp[6] = 1, dp[5] = 1, dp[3] = 3, dp[2] = 2

*/
