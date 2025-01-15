/* 題目是找出和num2一樣多的set bit 且和num1 xor之後最小
 * xor最小就是和num1最大的set bit一樣 多出來的在從num1 LSB開始取
 *
 * time  : O(1)
 * space : O(1)
 */
class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int cnt = __builtin_popcount(num2);
        int i = 31, ans{};
        while(cnt && i >= 0) {
            if((num1 >> i) & 1) {
                cnt--;
                ans |= 1 << i;
            }
            i--;
        }
        i = 0;
        while(i < 32 && cnt) {
            if(((num1 >> i) & 1) == 0) {
                cnt--;
                ans |= 1 << i;
            }
            i++;
        }
        return ans;
    }
};
/* 使用bitset改寫
 *
 */
class Solution {
public:
    int minimizeXor(int num1, int num2) {
        int cnt = __builtin_popcount(num2);
        int i = 31;
        bitset<32> ans{}, bnum1(num1);
        while(cnt && i >= 0) {
            if(bnum1.test(i)) {
                cnt--;
                ans.set(i);
            }
            i--;
        }
        i = 0;
        while(i < 32 && cnt) {
            if(!bnum1.test(i)) {
                cnt--;
                ans.set(i);
            }
            i++;
        }
        return (int)ans.to_ulong();
    }
};
