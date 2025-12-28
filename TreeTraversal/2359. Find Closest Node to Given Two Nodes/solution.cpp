/*  參考hint 先找出node1和node2對每個點的最短距離
 *           然後找出符合題目的條件
 */
class Solution {
    vector<int> helper(vector<int>& edges, int node) {
        int sz = edges.size();
        vector<int> rtn(sz, sz);
        rtn[node] = 0;
        queue<int> q;
        q.push(node);
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            int nxt = edges[cur];
            if(nxt != -1 && rtn[cur] + 1 < rtn[nxt]) {
                rtn[nxt] = rtn[cur] + 1;
                q.push(nxt);
            }
        }
        return rtn;
    }
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int sz = edges.size();
        vector<int> vec1 = helper(edges, node1);
        vector<int> vec2 = helper(edges, node2);
        int rtn{-1}, dist = sz;
        for(int i = 0; i < sz; ++i)
            if(dist > max(vec1[i], vec2[i])) {
                dist = max(vec1[i], vec2[i]);
                rtn = i;
            }
        return rtn;
    }
};
