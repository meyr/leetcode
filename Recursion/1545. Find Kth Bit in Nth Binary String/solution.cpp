/*  因為事先已經知道是recursive的題目 所以就是遞減n來推算k的位置所在char
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    int helper(int n, int k) {
        if(n == 1) return 0;
        else if(k > 1 && (k & (k - 1)) == 0) return 1;
        else if(k > pow(2, n - 1)) return !helper(n - 1, pow(2, n) - k);
        else return helper(n - 1, k);
    }
public:
    char findKthBit(int n, int k) {
        return helper(n, k) + '0';
    }
};
/*
    1 = 0                 1
    2 = 011               3
    3 = 0111001           7
    4 = 01110011 0110001  15

    1, 2, 3, 4, 5, 6, 7
    0, 1, 1, 1, 0, 0, 1

*/
