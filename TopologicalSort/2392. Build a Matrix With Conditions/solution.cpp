/*
 *  參考：
 *  https://leetcode.com/problems/build-a-matrix-with-conditions/solutions/5508632/beats-100-explained-with-video-c-java-python-js-topological-sort-explained-in-detail/
 *
 *
 *
 */
class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions) {
        vector<vector<int>> rowGraph(k + 1), colGraph(k + 1); // 先從rowConditions和colConditions建立關係
        for (auto& rc : rowConditions) {
            rowGraph[rc[0]].push_back(rc[1]);
        }
        for (auto& cc : colConditions) {
            colGraph[cc[0]].push_back(cc[1]);
        }

        vector<int> rowOrder = topoSort(rowGraph, k);	// 使用topological sort 取得node的前後關係
        vector<int> colOrder = topoSort(colGraph, k);

        if (rowOrder.empty() || colOrder.empty()) return {};

        vector<vector<int>> result(k, vector<int>(k, 0));
        unordered_map<int, int> rowMap, colMap;
        for (int i = 0; i < k; ++i) {
            rowMap[rowOrder[i]] = i; // rowOrder = [1, 3, 2], rowMap = {{1, 0},{3, 1}, {2, 2}}
            colMap[colOrder[i]] = i;
        }
		/*    [1, 1, 1]   rowOrder = [1, 3, 2]
		 *    [3, 3, 3]
		 *    [2, 2, 2]
		 */

        for (int i = 1; i <= k; ++i) {
            result[rowMap[i]][colMap[i]] = i;
        }

        return result;
    }

    vector<int> topoSort(vector<vector<int>>& graph, int k) {
        vector<int> inDegree(k + 1, 0), order;
        queue<int> q;
        for (int i = 1; i <= k; ++i) {
            for (int j : graph[i]) {
                ++inDegree[j];
            }
        }
        for (int i = 1; i <= k; ++i) {
            if (inDegree[i] == 0) q.push(i);
        }
        while (!q.empty()) {
            int node = q.front(); q.pop();
            order.push_back(node);
            for (int adj : graph[node]) {
                if (--inDegree[adj] == 0) q.push(adj);
            }
        }
        return order.size() == k ? order : vector<int>(); // 為什麼order.size() != k 返回empty？
														  // 表示有loop所以答案不存在
    }
};
