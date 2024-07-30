/*
 *  參考 : https://leetcode.cn/problems/double-modular-exponentiation/solutions/2857776/shuang-mo-mi-yun-suan-by-leetcode-soluti-tque/ 
 *  
 *  快速計算power和mod
 *  計算power最快的方法就是奇數 res = res * a % mod;
 *                         偶數   a =   a * a % mod;
 *  
 */
class Solution {
    int pow_mod(int a, int b, int m) {
        int res{1};
        while(b) {
            if(b & 1) res = (res * a) % m;
            a = (a * a) % m;
            b >>= 1;
        }
        return res;
    }
public:
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) {
        vector<int> ans;
        for(int i = 0; i < variables.size(); ++i) {
            vector<int>& v = variables[i];
            if(pow_mod(pow_mod(v[0], v[1], 10), v[2], v[3]) == target)
                ans.push_back(i);
        }
        return ans;
    }
};
