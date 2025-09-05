/*
    num1 - (2^k1 + num2) - (2^k2 + num2) - ... - (2^kn + num2) = 0    假設經過n次operation就會等於0
    num1 - N * num2 - (2^k1 + 2^k2 + ... + 2^kn) = 0
    num1 - N * num2 = 2^k1 + 2^k2 + ... + 2^kn  , 如果照著每個set bit拆解 那麼__最少次__需要__builtin_popcount(num1 - N* num2) 所以 n >= __builtin_popcount(num1 - N * num2)

    num1 - N * num2 = diff, 如果都使用最小值 2^0 = 1也需要diff(最多次)次操作才可以拼成diff。
    所以 N > diff就不可能拼成 所以另一個條件是 N <= diff

    3 - 1*(-2) = 5 = 0b101 = 2 > 1
    3 - 2*(-2) = 7 = 0b111 = 3 > 2
    3 - 3*(-2) = 9 = 0b1001 = 2 <= 3

      
*/

class Solution {
public:
    int makeTheIntegerZero(int x, int y) {
        for(int k = 1; k < 61; ++k) {
            long long diff = x - k * (long long)y;
            if(__builtin_popcountll(diff) <= k && k <= diff)   // 敘述 k 最多次和最少次的條件
                return k;                                      // __important__ 另一個重點是使用 __builtin_popcountll()  這是針對 long long 64bit
        }                                                      //                                __builtin_popcountl()       針對 long int 32bit
                                                               //                                __builtin_popcount()        針對 int 32bit
        return -1;
    }
};
