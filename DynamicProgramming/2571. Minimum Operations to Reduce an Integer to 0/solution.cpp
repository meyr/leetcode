/*  嘗試在lsb 1進行兩種操作
 *
 */
class Solution {
    unordered_map<int, int> um;
public:
    int minOperations(int n) {
        int rtn{};
        if(um.count(n)) return um[n];
        auto count = __builtin_popcount(n);
        if(count <= 1) rtn = count;
        else {
            int shift = __builtin_ffs(n) - 1;
            rtn = min(minOperations(n + (1 << shift)), 
                       minOperations(n - (1 << shift))) + 1;
        }
        return um[n] = rtn;
    }
};
