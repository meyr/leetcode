/*  why binary search?
 *
 *  一開始我是使用bfs結果是TLE,
 *  參考leetcode官方解答 是使用binary search + shortest path
 *  因為這邊有兩個限制一個是total cost另一個是minimal cost
 *  如果使用這兩個變數來建表 表格會很大
 *
 *  如果使用binary search來找minimal cost這樣我們可以固定一個變數
 *  這樣只要考慮total cost <= k 就可以
 *
 *  minimal cost : 0, 1, 2, 3, 4, 5
 *  check        : o, o, o, x, x, x    minimal cost越小表示可以使用的edge越多 越能達到n - 1
 *
 *  所以答案是left - 1
 *  必須先檢查 check(left) 因為如果最小值都過不了了 那就沒有數值可以過得了
 *
 */
class Solution {
    using ll = long long;
    template<typename T>
    using minheap = priority_queue<T, vector<T>, greater<>>;
    unordered_map<int, vector<vector<int>>> adj;
    ll k;
    int n;
    bool check(int minCost) {
        minheap<pair<ll, int>> pq; // total cost, node
        vector<ll> costs(n, LLONG_MAX);
        costs[0] = 0;
        pq.push({0, 0});
        while(!pq.empty()) {
            auto [sum, from] = pq.top(); pq.pop();
            if(from == n - 1) return true;
            if(sum > costs[from] || sum > k) continue;
            for(const auto& childs : adj[from]) {
                int to = childs[0], c = childs[1];
                if(c < minCost || sum + c >= costs[to] || sum + c > k) continue;
                costs[to] = sum + c;
                pq.push({costs[to], to});
            }
        }
        return false;
    }
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        if(!online.front() || !online.back()) return -1;
        n = online.size();
        this->k = k;
        int left{INT_MAX}, right{INT_MIN};
        for(const auto& e : edges) {
            if(online[e[0]] && online[e[1]]) {
                adj[e[0]].push_back({e[1], e[2]});
                left = min(left, e[2]);
                right = max(right, e[2]);
            }
        }
        right++;
        if(!check(left)) return -1;
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(check(mid)) left = mid + 1;
            else right = mid;
        }
        return left - 1;
    }
};
