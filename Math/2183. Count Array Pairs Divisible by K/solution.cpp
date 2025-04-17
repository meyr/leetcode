/*  參考 : https://leetcode.com/problems/count-array-pairs-divisible-by-k/solutions/1785906/how-gcdak-gcdbk-k-0-explained-with-examp-51jy/
 * 
 *  n * m % k = 0
 *  gcd(n, k) * gcd(m, k) % k = 0
 * 
 *  所有的數都可以分解成質數相乘 n = p1^c1n * p2^c2n * p3^c3n  其中p1, p2, p3為質數
 *                               k =          p2^c2k * p3^c3k
 *
 *                  則gcd(n, k)    =          p2^min(c2n, c2k) * p3^min(c3n, c3k)  gcd就是n和k的prime交集, prime可以視為組成元素, p1沒出現在k中所以不用管它
 *                    gcd(m, k)                                                           m和k的prime交集
 *
 *                    所以gcd(n, k)*gcd(m, k)為 可以組出來的所有primey再確定是否可以被k整除即可
 *                    gcd(n, k) 縮小需要儲存的數量 但是卻儲存和k最相關的prime數量
 *
 *  類似題目: 2176. Count Equal and Divisible Pairs in an Array 
 */
class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        long long ans{};
        unordered_map<int, int> um_gcds;
        for(auto& n : nums) {
            long long gcd_n = __gcd(n, k);
            for(auto& [gcd_m, cnt] : um_gcds) {
                if(gcd_n * gcd_m % k == 0)
                    ans += cnt;
            }
            um_gcds[gcd_n]++;
        }
        return ans;
    }
};
