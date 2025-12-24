/*  
 *  第k個level的朋友的定義是 從0開始到x的最短距離 所以需要一個vector<int> lv來記錄最短距離
 *  有了vector<int> lv之後就是統計第k個level的朋友看了那些video並且排序
 * 
 */
class Solution {
    void bfs(vector<vector<int>>& friends, vector<int>& lv, int id, int target) {
        queue<int> q{{id}};
        int level = 1;
        unordered_set<int> visited;
        visited.insert(id);
        while(level <= target) {
            for(int loop = q.size(); loop > 0; --loop) {
                int cur = q.front(); q.pop();
                for(auto& nxt : friends[cur]) {
                    if(lv[nxt] > lv[cur] + 1)
                        lv[nxt] = lv[cur] + 1;
                    if(visited.count(nxt)) continue;
                    q.push(nxt);
                    visited.insert(nxt);
                }
            }
            level++;
        }
    }
public:
    vector<string> watchedVideosByFriends(vector<vector<string>>& watchedVideos, vector<vector<int>>& friends, int id, int level) {
        int sz = friends.size();
        vector<int> lv(sz, INT_MAX);
        lv[id] = 0;
        bfs(friends, lv, id, level);
        unordered_map<string, int> freq;
        for(int i = 0; i < sz; ++i) {
            if(lv[i] == level) {
                for(auto& v : watchedVideos[i])
                    freq[v]++;
            }
        }
        vector<string> rtn;
        for(auto& ref : freq)
            rtn.push_back(ref.first);
        sort(begin(rtn), end(rtn), [&](auto& a, auto& b){
            if(freq[a] < freq[b]) return true;
            else if(freq[a] == freq[b]) return a < b;
            else return false;
        });
        return rtn;
    }
};
