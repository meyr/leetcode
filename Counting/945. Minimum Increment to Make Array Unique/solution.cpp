/*
 *   因為每一次move只能+1 所以等於把數值持續往上推
 *
 *   time  : O(N)
 *   space : O(1)
 */
class Solution {
public:
    int minIncrementForUnique(vector<int>& nums) {
        vector<int> st(1e5 + 1);
        for(auto& n : nums) st[n]++;
        int ans{};
        for(int i = 0; i < 1e5; ++i) {
            if(st[i] <= 1) continue;
            ans += st[i] - 1;
            st[i + 1] += st[i] - 1;
        }
        if(st.back() != 0) {
            int n = st.back() - 1;
            ans += (1 + n) * n / 2;
        }
        return ans;
    }
};
/*
    1e5 : 5

    1e5    : 1
    1e5 + 1: 1
    1e5 + 2: 1
    1e5 + 3: 1
    1e5 + 4: 1
*/

