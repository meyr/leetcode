/* 參考 : 2081. Sum of k-Mirror Numbers 解答 
 *
 */
class Solution {
    bool isPrime(int val) {
        if(val == 1) return false;
        for(int i = 2; i <= sqrt(val); ++i)
            if(val % i == 0) return false;
        return true;
    }
public:
    int primePalindrome(int n) {
        for(int left = 1, right = 10;; left = right, right *= 10) {
            for(int op = 0; op < 2; ++op) {
                for(int i = left; i < right; ++i) {
                    int comb = i;
                    int x = op == 0 ? i / 10 : i;
                    while(x) {
                        comb = comb * 10 + x % 10;
                        x /= 10;
                    }
                    if(comb < n) continue;
                    if(isPrime(comb))
                        return comb;
                }
            }
        }
        return -1;
    }
};
