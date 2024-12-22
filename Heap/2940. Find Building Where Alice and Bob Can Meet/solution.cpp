/*
    參考: https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/solutions/4304269/javacpython-priority-queue-by-lee215-11js/

    只能從index小跳到index大，且必須跳到比自己高度還高(i < j && heights[j] > heights[i])
    case 1: index of alice == index of bob --> index of bob
    case 2: heights[alice] < heights[bob]  --> index of bob
    case 3: heights[alice] > heights[bob]  --> 必須查詢才知道，跳到哪一個leftmode index

    因為答案和查詢的bob位置有關，所以que儲存每個查詢bob的index其中{heights[alice], index of query}

*/
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& A, vector<vector<int>>& queries) {
        int n = A.size(), qn = queries.size();
        vector<vector<vector<int>>> que(n);
        priority_queue<vector<int>, vector<vector<int>>, greater<>> h; //minheap <height of alice, index of query>
        vector<int> res(qn, -1);
        // Step 1
        for (int qi = 0; qi < qn; qi++) {
            int i = queries[qi][0], j = queries[qi][1];
            if(i > j) swap(i, j);
            if(i == j || A[j] > A[i]) res[qi] = j;
            else que[j].push_back({A[i], qi}); // 需要查詢bob, 因為需要查詢的bob可能重複，所以紀錄alice高度和query index
                                               //         qe[index of bob][height of alice][index of query]
        }
        // Step 3
        for (int i = 0; i < n; i++) {
            while (!h.empty() && h.top()[0] < A[i]) { // bob高度比alice還高
                res[h.top()[1]] = i;
                h.pop();
            }
            for (auto& q : que[i]) { // 加入這個index後需要查詢的item
                h.push(q);
            }
        }
        return res;
    }
};
