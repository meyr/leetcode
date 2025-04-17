/*   參考 : https://leetcode.com/problems/count-equal-and-divisible-pairs-in-an-array/solutions/1784521/on-sqrt-n-by-votrubac-uue1/
 *          2183. Count Array Pairs Divisible by K
 *
 *   使用兩個for loop就可以暴力破解 但是可以參考2183的解法    
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
