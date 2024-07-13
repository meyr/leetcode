/*
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int sz = positions.size();
        vector<int> m(sz);	// 紀錄每個的index之後在根據positions[i]來排序
        iota(m.begin(), m.end(), 0); // O(N)
        sort(m.begin(), m.end(), [&](int a, int b){ // O(NlogN)
            return positions[a] < positions[b];
        });
        stack<int> st; // index
        for(auto& i : m) { // O(N)
            bool add = true;
            while(!st.empty() && directions[i] == 'L' && directions[st.top()] == 'R') {
                if(healths[st.top()] == healths[i]) {
                    add = false;
                    healths[st.top()] = 0;	// 把healths設為0 方便以後答案可以判斷
                    healths[i] = 0;
                    st.pop();
                    break;
                } else if(healths[st.top()] > healths[i]) {
                    add = false;
                    healths[i] = 0;
                    healths[st.top()]--;
                    break;
                } else {
                    healths[st.top()] = 0;
                    st.pop();
                    healths[i]--;
                }
            }
            if(add) st.push(i);
        }
        vector<int> ans;
        for(int i = 0; i < healths.size(); ++i) // O(N)
            if(healths[i] != 0) ans.push_back(healths[i]);
        return ans;
    }
};
