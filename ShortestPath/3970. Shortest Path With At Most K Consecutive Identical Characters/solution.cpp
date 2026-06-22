/*  一開始寫的解答如下 怎麼寫都會有testcase無法過
 */
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        unordered_map<int, vector<vector<int>>> adj; // from, <to, weight>
        for(auto& e : edges)
            adj[e[0]].push_back({e[1], e[2]});
        vector<int> minDist(n, INT_MAX);
        minDist[0] = 0;
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq; // minheap, <weight, node, k>
        pq.push({0, 0, k - 1});
        while(!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            int weight = cur[0], from = cur[1], rem = cur[2];
            if(from == n - 1) return weight;
            if(weight > minDist[from]) continue;
            for(auto& nxt : adj[from]) {
                int to = nxt[0], w = nxt[1];
                if(w + weight < minDist[to]) {
                    if(labels[to] == labels[from]) {
                        if(rem) {
                            pq.push({w + weight, to, rem - 1});
                            minDist[to] = w + weight;
                        }
                    } else {
                        pq.push({w + weight, to, k - 1});
                        minDist[to] = w + weight;
                    }
                }
            }
        }
        return -1;
    }
};
/*  參考AI的解答 __importatn__ 少考慮了一個條件 每個node除了到達此node的最少weight還需要考慮到達有多少個連續char
 *                                              因為不同的連續char可以有不同的weight 所以必須定義成 dist[weight][連續char]
 *
 *
 */
class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (auto& e : edges)
            adj[e[0]].push_back({e[1], e[2]}); // to, weight

        vector<vector<int>> dist(n, vector<int>(k + 1, INT_MAX));
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq; // weight, node, Consecutive Identical Characters
        dist[0][1] = 0;
        pq.push({0, 0, 1}); // 一開始有一個連續的char

        while (!pq.empty()) {
            auto curState = pq.top();pq.pop();
            int weight = curState[0], cur = curState[1], cnt = curState[2];
            if (weight > dist[cur][cnt]) continue;
            if (cur == n - 1) return weight;
            for (auto& edge : adj[cur]) {
                int nxt = edge.first;
                int w = edge.second;
                int nxt_cnt = (labels[cur] == labels[nxt]) ? cnt + 1 : 1;
                if (nxt_cnt > k) continue;
                if (weight + w < dist[nxt][nxt_cnt]) {
                    dist[nxt][nxt_cnt] = weight + w;
                    pq.push({dist[nxt][nxt_cnt], nxt, nxt_cnt});
                }
            }
        }

        return -1;
    }
};
