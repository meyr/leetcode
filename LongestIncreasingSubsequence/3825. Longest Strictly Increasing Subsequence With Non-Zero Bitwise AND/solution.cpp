/*  因為sequence bitwise不能為0 意思是sequence中有個bit大家都會有
 *  所以使用bit來分類 sequence
 *
 *  time  : O(32 * NlogN) = O(NlogN)
 *  space : O(32N) = O(N)
 *
 */
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        vector<vector<int>> bits(32, vector<int>());
        int ans{};
        auto lis = [](vector<int>& vec, int n)->int {
            auto it = lower_bound(begin(vec), end(vec), n);
            if(it == vec.end()) vec.push_back(n);
            else *it = n;
            return vec.size();
        };
        for(auto& n : nums) {
            for(int b = 0; b < 32; ++b) {
                if(n & (1 << b))
                    ans = max(ans, lis(bits[b], n));
            }
        }
        return ans;
    }
};
