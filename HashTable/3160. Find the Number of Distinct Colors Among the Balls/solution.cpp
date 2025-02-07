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
/*  2025/02/07 daily challenge
 *  
 *  分別使用unordered_map<int, int> c, m來記錄ball to color, 和每個color的count
 *  time  : O(N)
 *  space : O(M), N : size of queries, M : limit
 */
class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) {
        unordered_map<int, int> c, m;
        vector<int> rtn;
        int count{};
        for(const auto& q : queries) {
            int node = q[0], color = q[1];
            if(c.count(node))
                if(--m[c[node]] == 0) count--;
            c[node] = color;
            if(m[color]++ == 0) count++;
            rtn.push_back(count);
        }
        return rtn;
    }
};
