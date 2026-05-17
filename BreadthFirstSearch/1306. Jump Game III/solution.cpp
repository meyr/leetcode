/*  一開始我使用UnionFind但是無法AC
 *  忽略到了一個點 當你使用UnionFind是雙向都可以通 但是 i 可以跳到i + arr[i] 或是 i - arr[i]
 *  不保證 i + arr[i] 可以跳回 i 
 *
 *  所以使用BFS
 *
 *  time  : O(N) 每個點只會走過一次
 *  space : O(N)
 */
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int sz = arr.size();
        queue<int> q{{start}};
        unordered_set<int> visited{start};
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            if(arr[cur] == 0) return true;
            for(int nxt : {cur + arr[cur], cur - arr[cur]}) {
                if(nxt < 0 || nxt >= sz || visited.count(nxt)) continue;
                q.push(nxt);
                visited.insert(nxt);
            }
        }
        return false;
    }
};
