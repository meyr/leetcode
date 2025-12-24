/*
 *  紀錄 node to group和 group to node的兩個map
 *
 */
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if(source == target) return 0;
        unordered_map<int, vector<int>> n2g;
        unordered_map<int, vector<int>> g2n;
        for(int g = 0; g < routes.size(); ++g) {
            for(auto& n : routes[g]) {
                n2g[n].push_back(g);
                g2n[g].push_back(n);
            }
        }
        unordered_set<int> tg(begin(n2g[target]), end(n2g[target]));
        queue<int> q;
        unordered_set<int> visited;
        for(auto& g : n2g[source]) {
            q.push(g);
            visited.insert(g);
        }
        int ans{1};
        while(!q.empty()) {
            for(int loop = q.size(); loop > 0; --loop) {
                int g = q.front(); q.pop();
                if(tg.count(g)) return ans;
                unordered_set<int> ng;
                for(auto& member : g2n[g])
                    for(auto& nxtg : n2g[member])
                        if(!visited.count(nxtg)) {
                            ng.insert(nxtg);
                            visited.insert(nxtg);
                        }
                for(auto& n : ng)
                    q.push(n);
            }
            ans++;
        }
        return -1;
    }
};
