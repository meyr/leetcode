/* 參考 : https://leetcode.com/problems/count-number-of-balanced-permutations/solutions/6000532/dp-by-votrubac-7x53/
 * 自己寫出c++版本但是TLE
 *
 */
class Solution {
    int mod = 1e9 + 7;
    vector<vector<int>> comb;
    vector<vector<vector<vector<int>>>> mem;
    vector<int> cnt;
    void create_comb_table() {                  // __important__ pascal's triangle
        comb.resize(81, vector<int>(81));       // ref : https://zhuanlan.zhihu.com/p/257895125
        for(int i = 0; i <= 80; i++){           // (a+b)^n = comb(n, 0)*a^n*b^0 + comb(n,1)*a^(n-1)*b^1 + comb(n,2)*a^(n-2)*b^2 + ... + comb(n,n)*a^0*b^n
            comb[i][0] = comb[i][i] = 1;        // 根據pascal's triangle --> comb(n, k) = comb(n - 1, k) + comb(n - 1, k - 1), triangle的前後都是1 --> comb[i][0] = comb[i][i] = 1
            for(int j = 1; j <= i; j++)         // j = 1; j <= i    最少取1個最多取i個
                comb[i][j]= (comb[i-1][j] + comb[i-1][j-1]) % mod;
        }
    }
    int helper(int idx, int odd, int even, int total) {
        if(odd == 0 && even == 0) return total == 0;                            // even, odd 格子都使用完了 可以判斷total是否為0
        else if(idx < 0 || odd < 0 || even < 0 || total < 0) return 0;          // 格子不夠 或是 total < 0 不可能組成答案
        else if(~mem[idx][odd][even][total]) return mem[idx][odd][even][total];
        int res{};
        for(int i = 0; i <= cnt[idx]; ++i)                                      // 數字idx, ex: 9, 有cnt[idx]這麼多個, 拿i個放到odd, 則剩下cnt[idx] - i放到even, 所有的組合就是comb(odd, i)*comb(even, cnt[idx] - i)
            res = (res + comb[odd][i] * comb[even][cnt[idx] - i] * helper(idx - 1, odd - i, even - cnt[idx] + i, total - i * idx)) % mod;
        return mem[idx][odd][even][total] = res;
    }
public:
    int countBalancedPermutations(string num) {
        int sum{};
        cnt.resize(10);
        for(auto& n : num) {
            cnt[n - '0']++;
            sum += n - '0';
        }
        if(sum % 2 == 1) return 0;
        create_comb_table();
        mem.resize(10, vector<vector<vector<int>>>(42, vector<vector<int>>(41, vector<int>(361, -1))));
        return helper(9, num.size() - num.size() / 2, num.size() / 2, sum / 2);
    }
};
