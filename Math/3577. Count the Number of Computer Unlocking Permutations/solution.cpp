/*  參考hint
 *
 *  因為解鎖的條件是 使用比自己小的index 且 complexity也要比自己小 
 *  也就是   computer  :    j.....i
 *           complexity:   c[j]   c[i]     其中j < i 且 c[j] < c[i]
 *
 *  只要root 可以保證是最小值 其他都可以使用root來解 所以排列數就是 (sz - 1)!
 *
 *  time  : O(N + N) = O(N)
 *  space : O(1)
 */ 
class Solution {
public:
    int countPermutations(vector<int>& complexity) {
        int minv = *min_element(begin(complexity) + 1, end(complexity));
        if(minv <= complexity[0]) return 0;
        else {
            int mod = 1e9 + 7;
            int n = 1, sz = complexity.size(), rtn{1};
            while(n <= sz - 1)
                rtn = ((long long)rtn * n++) % mod;
            return rtn;
        }
    }
};
