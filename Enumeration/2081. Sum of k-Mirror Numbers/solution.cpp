/*  參考: https://leetcode.cn/problems/sum-of-k-mirror-numbers/solutions/1115277/k-jing-xiang-shu-zi-de-he-by-leetcode-so-nyos/
 *
 *  1. 列舉base-10 所有的mirror number
 *  2. 檢查這些mirror number是否符合base-k mirror
 *
 *  列舉所有的數是不可能的會TLE 所以使用拚的
 *  例如: i = 1, 2, 3, 4, ...9  (left = 1, right  = 10)
 *  可以拚出奇數(1, 2, 3...9) 和偶數(11, 22, ..., 99)
 *
 *  例如: i = 10, 11, 12, 13, ..., 20, 21, 22, 23,..., 30, 31, 32, 33, ..., 90, 91, 92, 93, ..., 99  (left = 10, right  = 100)
 *  可以拚出奇數(101, 111, 121, 131, ...) 和偶數(1001, 1111, 1221, 1331, ...)
 *  
 *  先拚奇數再拚偶數因為才是從小到大排列
 *  
 */
class Solution {
private:
    int digit[100];
public:
    long long kMirror(int k, int n) {
        auto isPalindrome = [&](long long x) -> bool {
            int length = -1;
            while (x) {
                ++length;
                digit[length] = x % k;
                x /= k;
            }
            for (int i = 0, j = length; i < j; ++i, --j) {
                if (digit[i] != digit[j]) {
                    return false;
                }
            }
            return true;
        };

        int left = 1, count = 0;
        long long ans = 0;
        while (count < n) {
            int right = left * 10;
            // op = 0 表示枚举奇数长度回文，op = 1 表示枚举偶数长度回文
            for (int op = 0; op < 2; ++op) {
                // 枚举 i'
                for (int i = left; i < right && count < n; ++i) {
                    long long combined = i;
                    int x = (op == 0 ? i / 10 : i); // op == 0(奇數) i = 12, x = 1
                    while (x) {                     
                        combined = combined * 10 + x % 10;      // __important__ 拼出回文
                        x /= 10;
                    }
                    if (isPalindrome(combined)) {
                        ++count;
                        ans += combined;
                    }
                }
            }
            left = right;
        }
        return ans;
    }
};
/*  根據上面的概念 自己從寫了一次
 *
 */
class Solution {
    bool isPalindrome(long long val, int k) {
        vector<int> digit;
        while(val) {
            digit.push_back(val % k);
            val /= k;
        }
        for(int i = 0, j = digit.size() - 1; i < j; ++i, --j)
            if(digit[i] != digit[j])
                return false;
        return true;
    }
public:
    long long kMirror(int k, int n) {
        long long ans{};
        for(int left = 1, right = 10; n > 0; left = right, right *= 10) {
            for(int op = 0; op < 2; ++op) { // odd first then even
                for(int i = left; n > 0 && i < right; ++i) {
                    long long comb = i;
                    int x = op == 0 ? i / 10 : i;   // x = 123
                    while(x) {                      // 1233, 12332, 12331
                        comb = comb * 10 + x % 10;
                        x /= 10;
                    }
                    if(isPalindrome(comb, k)) {
                        ans += comb;
                        n--;
                    }
                }
            }
        }
        return ans;
    }
};
