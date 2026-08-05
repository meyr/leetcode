/*  怎麼寫都怪怪的 直接參考官方解答
 *  我覺得是對題目的不理解
 *  只要正常的method呼叫到suspicious method就不能移除
 *  也就是suspicious method都是suspicious呼叫才可以全部移除
 *
 */
constexpr int MAXN = 100005;

class Solution {
public:
    vector<int> remainingMethods(int n, int k,
                                 vector<vector<int>>& invocations) {
        vector<vector<int>> edges(n);
        vector<int> inDegree(n, 0);
        bitset<MAXN> suspicious;
        for (const auto& inv : invocations) {
            edges[inv[0]].push_back(inv[1]);
            inDegree[inv[1]]++; // 多少個正常method呼叫它
        }

        queue<int> q;
        q.push(k);
        suspicious.set(k);                  // 紀錄那些method是suspicious
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : edges[u]) {
                inDegree[v]--;              // 扣掉suspicious呼叫, indegree表示正常method呼叫的次數
                if (!suspicious.test(v)) {
                    q.push(v);
                    suspicious.set(v);
                }
            }
        }

        bool canRemoveAll = true;
        vector<int> remaining;
        for (int i = 0; i < n; i++) {
            if (suspicious.test(i) && inDegree[i] > 0) {    // 是suspicious且有正常的method呼叫 那就不能移除
                canRemoveAll = false;
                break;
            } else if (!suspicious.test(i)) {   // 正常method放入remaining
                remaining.push_back(i);
            }
        }

        if (!canRemoveAll) {
            vector<int> allNodes(n);
            iota(allNodes.begin(), allNodes.end(), 0);
            return allNodes;
        }

        return remaining;
    }
};
