/*
 * 很明顯示最短距離問題 使用floyd-washer
 * time  : O(N + 26^3 + M) = O(N + M), N : size of original, M : size of source
 * space : O(26^2) = O(1)
 */

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        vector<vector<int>> dist(26, vector<int>(26, 1e9));
        for(int i = 0; i < original.size(); ++i) {
            char s = original[i] - 'a', t = changed[i] - 'a';
            int c = cost[i];
            dist[s][t] = min(dist[s][t], c);
        }
        for(int k = 0; k < 26; ++k)
            for(int i = 0; i < 26; ++i)
                for(int j = 0; j < 26; ++j)
                    if(i != k && j != k && i != j && dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];
        long long ans{};
        for(int i = 0; i < source.size(); ++i) {
            char c = source[i] - 'a', t = target[i] - 'a';
            if(c != t) {
                if(dist[c][t] >= 1e9) return -1;
                else ans += dist[c][t];
            }
        }
        return ans;
    }
};
