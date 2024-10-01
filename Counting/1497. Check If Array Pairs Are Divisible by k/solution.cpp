/*
 * 計算每個數值mod k之後的值 可以被整除意味著取 mod k == n 和 mod k == k - n 當成一個pair
 * 所以mod k == n 必須和 mod k == k - n個數要一樣
 *
 *  time  : O(N + K)
 *  space : O(N)
 */
class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        vector<int> m(k);
        for(auto& n : arr) m[((n % k) + k) % k]++;
        if(m[0] % 2 == 1) return false;
        for(int i = 1; i <= k / 2; ++i) {
            if(m[i] != m[k - i]) return false;
        }
        return true;
    }
};
