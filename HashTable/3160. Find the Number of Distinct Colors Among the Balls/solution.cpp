/*
    limit = 4

    ball                queries
    0, 1, 2, 3, 4       [0, 1], [1, 2], [2, 2], [3, 4], [4, 5]
    1
    1, 2
    1, 2, 2
    1, 2, 2, 4
    1, 2, 2, 4, 5


    time  : O(N)
*/

class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        vector<int> ans;
        unordered_map<int, int> ball;
        unordered_map<int, int> cs; // value, count
        int cnt{};
        for(auto& q : queries) {
            int idx = q[0], color = q[1];
            if(!ball.count(idx)) {
                if(cs[color]++ == 0) cnt++;
                ball[idx] = color;
            } else if(color != ball[idx]) {
                if(--cs[ball[idx]] == 0) cnt--;
                if(cs[color]++ == 0) cnt++;
                ball[idx] = color;
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};


