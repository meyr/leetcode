/*
 *  因為計算score的方法為 min(nums[i], nums[i + 1], ... nums[j - 1], nums[j]) * (j - i + 1)
 *  為標準的使用monotonic stack找出小於自己的兩個邊界
 *
 *  另外有k這個限制 上下限必須在k裡面
 *
 *  time  : O(N)
 *  space : O(N)
 */

class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int sz = nums.size();
        vector<int> fwd(sz, sz), bwd(sz, -1);
        stack<int> st;
        for(int i = 0; i < sz; ++i) { // O(N)
            while(!st.empty() && nums[i] < nums[st.top()]) {
                fwd[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        stack<int>{}.swap(st);
        for(int i = sz - 1; i >= 0; --i) { // O(N)
            while(!st.empty() && nums[i] < nums[st.top()]) {
                bwd[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        int ans{};
        for(int i = 0; i < sz; ++i) { // O(N)
            if(bwd[i] < k && fwd[i] > k)
                ans = max(ans, nums[i] * (fwd[i] - bwd[i] - 1));
        }
        return ans;
    }
};
