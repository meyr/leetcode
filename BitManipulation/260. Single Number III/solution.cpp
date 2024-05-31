/*
 *  全部的數字都xor起來會得到 a^b 兩個不同數字的xor
 *  找出 a^b 第一個bit為1的 表示不同的地方 
 *  使用 bitmask & -bitmask 這技巧和BIT一樣找出 最低的set bit
 *
 *   10 = 0b1010 
 *  -10 = 0b0110
 *  --------------
 *        0b0010   <-- 只會取到最後一個bit
 *
 *  但是integer的範圍為-2147483648 to 2147483647
 *  -2147483648取negtive之後無法表達成 2147483648 
 *  所以比需轉成long
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int bitmask{};
        for(auto& n : nums) bitmask ^= n; // x^y
        int diff = bitmask & -(long)bitmask; // 1 : 代表次bit，x與y不同，所以我們可以使用此bit判斷
                                             // 目前的n是否包括x在裡面。
        int x = 0;
        for(auto& n : nums) {
            if(n & diff) x ^= n;
        }
        return {x, bitmask ^ x};
    }
};
