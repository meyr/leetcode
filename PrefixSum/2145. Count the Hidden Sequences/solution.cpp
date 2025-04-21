/* 
 *  假設n0 = 0 則可以依序推出每個數值  cur = d + prev 也就是計算prefix sum
 *  統計minv和maxv 因為minv 必須等於lower 所以maxv也跟著同步提上去 maxv + (lower - minv)
 *  最後計算maxv和upper的差距  upper - maxv' + 1 即為答案
 *
 *  idx:    0,       1,         2
 *   d :    1,      -3,         4
 *       n[1]-n[0]  n[2]-n[1]   n[3]-n[2]
 *
 *    n0    n1       n2         n3
 *     0   n1-0=1   n2-1=-3     n3+2=4
 *          n1=1    n2=-2       n3=2
 *                    minv       maxv      lower = 1, upper = 6
 *                    1            5          
 *
 *  time  : O(N)
 *  space : O(1)
*/
class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        long long minv{}, maxv{}, prev{};
        for(auto& d : differences) {
            long long cur = d + prev;
            minv = min(minv, cur);
            maxv = max(maxv, cur);
            prev = cur;
        }
        return max(0LL, upper - (maxv + (lower - minv)) + 1);
    }
};
