/*
 *  找出兩個non negative integer a, b使得a^2 + b^2 = c
 *  這邊我卡了一陣子 其中一個是non negative integer的定義是 0, 1, 2, 3, ... 有包括0
 *
 *  使用Two Pointers 也算是binary search
 *  time  : O(log(sqrt(c)))
 *  space : O(1)
 */
class Solution {
public:
    bool judgeSquareSum(int c) {
        if(c <= 2) return true;
        long left = 0, right = sqrt(c);
        while(left <= right) {
            long val = pow(left, 2) + pow(right, 2);
            if(val == c) return true;
            else if(val > c) right--;
            else left++;
        }
        return false;
    }
};
