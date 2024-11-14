/*  Good node的定義是 所以child node有相同的size
 *
 *  因為edges是描述 undirected tree 所以先建立 關係圖 unordered_map<int, vector<int>> m;
 *  依序訪問每個node並檢查child node的size是否相等
 *
 *  time  : O(E + N), E : sizeo of edges, N : number of nodes
 *  space : O(N + N + N) = O(N)
 */
class Solution {
    unordered_map<int, vector<int>> m;
    unordered_set<int> visited;
    int helper(int r, int& ans) {
        visited.insert(r);
        vector<int> cnt;
        for(auto& nxt : m[r]) {
            if(visited.count(nxt)) continue;
            cnt.push_back(helper(nxt, ans));
        }
        bool isAllTheSame{true};
        int total{};
        for(int i = 0; i < cnt.size(); ++i) {
            if(i > 0 && cnt[i] != cnt[i - 1]) isAllTheSame &= false;
            total += cnt[i];
        }
        ans += isAllTheSame;
        return total + 1;
    }
public:
    int countGoodNodes(vector<vector<int>>& edges) {
        int ans{};
        for(auto& e : edges) {
            m[e[0]].push_back(e[1]);
            m[e[1]].push_back(e[0]);
        }
        
        helper(0, ans);
        return ans;
    }
};
