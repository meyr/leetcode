/*
    target 的組合如下 因為要最小的sum 所以取左半部 移除掉右半部
	當 n <= m 的時候為special case 不需要移除右半部

    target = 6
    1, 5
    2, 4

    target = 7
    1, 6
    2, 5
    3, 4

    target = 50, n = 13
    1, 49
    2, 48
    3, 47
    4, 46
    ...
    24, 26
*/

class Solution {
public:
    int minimumPossibleSum(int n, int target) {
        if(n == 1) return 1;
        long m = (target - 1) / 2;
        long total = (1 + (n + m)) * (n + m) / 2;
        long remove = ((target - 1) + (target - m)) * (m) / 2;
        if(n <= m) return ((1 + n) * n / 2) % (int)(1e9 + 7);
        else return (total - remove) % (int)(1e9 + 7);
    }
    // time : O(1)
    // space : O(1) 
};


