/*
	因為可以循環 所以travesal array兩次
*/
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int sz = nums.size();
        vector<int> ans(sz, -1);
        stack<int> st;
        for(int i = 0; i < nums.size() * 2; ++i) {
            while(!st.empty() && nums[i % sz] > nums[st.top() % sz]) {
                ans[st.top() % sz] = nums[i % sz];
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};
