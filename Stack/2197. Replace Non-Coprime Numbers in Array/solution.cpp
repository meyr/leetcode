/*  按照題意 任意順序都可以得到相同結果 所以就從頭做到尾
 *
 *  time  : O(N)
 *  space : O(N)
 */

class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> rtn;
        for(auto n : nums) {
            while(!rtn.empty() && gcd(n, rtn.back()) > 1) {  // 判斷是否有non-coprime
                int g = gcd(n, rtn.back());
                int lcm = (long long)n * rtn.back() / g;
                rtn.pop_back();
                n = lcm;
            }
            rtn.push_back(n);
        }
        return rtn;
    }
};
