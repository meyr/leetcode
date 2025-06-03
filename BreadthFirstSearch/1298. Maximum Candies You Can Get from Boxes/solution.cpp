/*
 *  time  : O(N) 所有的boxes都走訪一次
 *  sapce : O(N)
 */
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        bitset<1001> st;                            // 可以打開的box
        for(int i = 0; i < status.size(); ++i)      // 本來就開啟的boxes
            if(status[i]) st.set(i);
        queue<int> q;
        unordered_set<int> bs;                      // 手上持有還不能開啟的boxes
        for(auto& b : initialBoxes) {
            if(st.test(b)) q.push(b);
            else bs.insert(b);
        }
        int ans{};
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            ans += candies[cur];
            for(auto& k : keys[cur]) {
                st.set(k);
                if(bs.count(k)) {
                    q.push(k);
                    bs.erase(k);
                }
            }
            for(auto& b : containedBoxes[cur]) {
                if(st.test(b)) q.push(b);
                else bs.insert(b);
            }
        }
        return ans;
    }
};
