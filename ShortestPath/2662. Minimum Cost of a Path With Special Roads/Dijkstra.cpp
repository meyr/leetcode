/*
 *   使用Dijkstra演算法 算出最短距離
 *   因為special road有起點和終點 等於是到達起點之後 可以用比較少的cost到達終點
 *
 */

template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
using LL = long long;
class Solution {
    int getDist(vector<int>& a, vector<int>& b) {
        return abs(a[0] - b[0]) + abs(a[1] - b[1]);
    }
    struct VectorHasher {
        int operator()(const vector<int> &V) const {
            int hash = V.size();
            for(auto &i : V) 
                hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
            return hash;
        }
    };
    unordered_map<vector<int>, LL, VectorHasher> dist; // 使用VectorHasher來達到使用vector<int>當index
public:
    int minimumCost(vector<int>& start, vector<int>& target, vector<vector<int>>& specialRoads) {
        dist[start] = 0;
        dist[target] = getDist(start, target);
        min_pq<pair<LL, vector<int>>> pq; // distance, encoded coordinate
        pq.push(make_pair(0, start));
        while(!pq.empty()) {
            auto [cur_dist, cur] = pq.top(); pq.pop();
            for(auto& r : specialRoads) {
                vector<int> f{r[0], r[1]};
                vector<int> t{r[2], r[3]};
                int c = r[4];
				// 因為使用了unordered_map來儲存distance所以必須多判斷使否存在
                if(!dist.count(t) || dist[t] > cur_dist + getDist(cur, f) + c) {
                    dist[t] = cur_dist + getDist(cur, f) + c;
                    pq.push(make_pair(dist[t], t));
					// 因為沒有node會連接到target 所以最後一段自己算
                    dist[target] = min(dist[target], dist[t] + getDist(t, target));
                }
            }
        }
        return dist[target];
    }
};
