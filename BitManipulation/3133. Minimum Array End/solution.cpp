/*
 * 一開始沒想出來 所以參考官方解答
 * https://leetcode.cn/problems/minimum-array-end/solutions/2885445/shu-zu-zui-hou-yi-ge-yuan-su-de-zui-xiao-4tbz/
 *
 * 因為AND的關係 所以 x 中bit為1的地方還是1 但是0的地方就可以放入數值
 * 這邊就是要把n - 1 放入x bit為0的地方
 *
 * time  : O(1)
 * space : O(1) 
 */
class Solution {
public:
    long long minEnd(int n, int x) {
        long long ans = x;
        int i{};
        n--;
        while(n) {
            while((ans >> i) & 1) i++; // 找出 ans中下一個bit 0 的位置
            ans |= ((long long)n & 1) << i++; // __important__ 必須把n轉成long long因為 i 有可能超過32
            n >>= 1;
        }
        return ans;
    }
};
