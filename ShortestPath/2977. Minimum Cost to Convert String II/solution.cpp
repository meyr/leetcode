/*  使用Floyd-Warshall + DP
 *
 *  1. 先把string對應成index
 *  2. 執行floyd-warshall 計算每個點到每個點的最短距離
 *  3. 使用DP來計算minimum cost
 */
class Solution {
    int count{};
    unordered_map<string, int> um; // string to index
    vector<vector<long long>> dist;
    vector<long long> mem;
    unordered_set<int> sublen;
    void init(vector<string>& original, vector<string>& changed, vector<int>& cost) {
        // string to index
        for(auto& w : original) {
            sublen.insert(w.size());
            if(!um.count(w))
                um[w] = count++;
        }
        for(auto& w : changed)
            if(!um.count(w))
                um[w] = count++;
        // floyd-warshall to calculate minimum distance
        dist.resize(um.size(), vector<long long>(um.size(), INT_MAX));
        for(int i = 0; i < um.size(); ++i) dist[i][i] = 0;
        for(int i = 0; i < original.size(); ++i) {
            int src = um[original[i]];
            int tar = um[changed[i]];
            dist[src][tar] = min(dist[src][tar], (long long)cost[i]);
        }
        for(int k = 0; k < um.size(); ++k) for(int i = 0; i < um.size(); ++i) for(int j = 0; j < um.size(); ++j) {
            if(i != k && j != k && i != j && dist[i][j] > dist[i][k] + dist[k][j])
                dist[i][j] = dist[i][k] + dist[k][j];
        }
    }
    // DP to get minimum cost
    long long helper(string& source, string& target, int idx) {
        if(~mem[idx]) return mem[idx];
        long long rtn = source[idx] == target[idx] ? helper(source, target, idx + 1) : 1e12;
        for(int len : sublen) { // __important__ 只找固定長度substring
            if(idx + len <= source.size()) {
                string src = source.substr(idx, len);
                string tar = target.substr(idx, len);
                if(!um.count(src) || !um.count(tar)) continue;
                if(dist[um[src]][um[tar]] < INT_MAX) {
                    rtn = min(rtn, helper(source, target, idx + len) + dist[um[src]][um[tar]]);
                }
            }
        }
        return mem[idx] = rtn;
    }
public:
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        init(original, changed, cost);
        mem.resize(source.size() + 1, -1);
        mem.back() = 0;
        auto rtn = helper(source, target, 0);
        return rtn >= 1e12 ? -1 : rtn;
    }
};
