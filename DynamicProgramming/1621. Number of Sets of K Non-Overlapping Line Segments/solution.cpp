/*
 *
 *      0,  1,  2,  3   n = 4, k = 2
 *      -----
 *          ====        interval不可以重疊 但是可以共享endpoint 而且最少要兩個point
 *                      所以等於是佔住一個間隔(點和點之間空間) 所以n point會有n - 1 space
 *
 *                      DP解法就是目前的interval可以佔幾個space
 *
 *      time  : O(N^2*K)    suboptimal solution
 *      space : O(NK)
 *
 */
class Solution {
    static constexpr int m = 1e9 + 7;
    int helper(int rem, int k) {
        if(k < 0) return 0;
        else if(rem <= 0) return k == 0;
        else if(k > rem) return 0;
        else if(k == rem) return 1;
        else if(~mem[rem][k]) return mem[rem][k];
        else {
            long long rtn = helper(rem - 1, k);
            for(int i = 1; rem - i >= k - 1; ++i)
                rtn = (rtn + helper(rem - i, k - 1)) % m;
            return mem[rem][k] = rtn;
        }
    }
    vector<vector<int>> mem;
public:
    int numberOfSets(int n, int k) {
        mem.resize(n, vector<int>(k + 1, -1));
        return helper(n - 1, k);
    }
};
