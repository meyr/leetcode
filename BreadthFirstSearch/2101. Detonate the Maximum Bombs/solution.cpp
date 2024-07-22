/*
 * 先建立每個bombs[i]可以引爆的index --> vector<vector<int>> det;
 * 使用BFS來看看引爆每個bombs[i]可以最多引爆的bombs
 *
 * time  : O(N^2 + N^2) = O(N^2)
 * space : O(N^2 + N + N) = O(N^2)
 */

class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int sz = bombs.size();
        vector<vector<int>> det(sz, vector<int>());
        for(int i = 0; i < sz; ++i) {
            vector<int>& a = bombs[i];
            for(int j = i + 1; j < sz; ++j) {
                vector<int>& b = bombs[j];
                double r = sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2));
                if(r <= a[2]) det[i].push_back(j);
                if(r <= b[2]) det[j].push_back(i);
            }
        }
        int ans{1};
        for(int i = 0; i < sz; ++i) {
            unordered_set<int> v{i};
            queue<int> q;
            q.push(i);
            while(!q.empty()) {
                int c = q.front(); q.pop();
                for(int nxt : det[c]) {
                    if(v.count(nxt)) continue;
                    v.insert(nxt);
                    q.push(nxt);
                }
            }
            ans = max(ans, (int)v.size());
        }
        return ans;
    }
};
