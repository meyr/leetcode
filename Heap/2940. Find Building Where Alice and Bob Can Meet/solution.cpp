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
/* 2025/12/30
 *
 * 想法是先排序queries 排除q[0] == q[1](已經相遇) 和heights[q[1]] > heights[q[0]](相遇在q[1])
 * 使用map來儲存遇到的heights 並且使用binary search來找出皆大於 heights[q[0]] 和 heights[q[1]] 的最小index
 */
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int sz = queries.size();
        vector<vector<int>> query;
        vector<int> rtn(sz, -1);
        for(int i = 0; i < sz; ++i) {
            vector<int>& q = queries[i];
            sort(begin(q), end(q));
            if(q[0] == q[1]) rtn[i] = q[1];
            else if(heights[q[1]] > heights[q[0]]) rtn[i] = q[1];
            else query.push_back({q[0], q[1], i});
        }
        sort(begin(query), end(query), [](auto& a, auto& b){
            return a[1] < b[1];
        });

        map<int, int> mp;
        for(int i = heights.size() - 1, j = query.size() - 1; j >= 0 && i >= 0; --i) {
            while(j >= 0 && i == query[j][1]) {
                auto it = mp.upper_bound(heights[query[j][0]]);
                if(it != mp.end()) {
                    int sidx = heights.size();
                    for(;it != mp.end(); ++it)
                        sidx = min(sidx, it->second);
                    rtn[query[j][2]] = sidx;
                }
                j--;
            }
            mp[heights[i]] = i;
        }
        return rtn;
    }
};
/* 
 * ref : https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/solutions/4304840/sort-queries-vs-exponential-monostack-by-6q5l/
 * 想法類似但是這邊使用了sorted queue 而不是像我使用map
 *
 * 想法就是index比較小且高度比較大 就可以取代之後比較小的高度
 *
 * vector<int> momo;
 *
 * idx : 0,    1,    2,    3,        新的height = 7 index = 3
 *      10(8) 9(7)  6(5)  4(4) <---> 7(3)
 *
 *      10(8) 9(7)  6(5)  7(3)
 *      10(8) 9(7)  7(3)
 *
 */
class Solution {
public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& qs) {
        vector<int> mono, idx, res(qs.size());
        for (int i = 0; i < qs.size(); ++i) {
            sort(begin(qs[i]), end(qs[i]));
            if (qs[i][0] == qs[i][1] || heights[qs[i][0]] < heights[qs[i][1]])  // 兩個位置一樣表示已經相遇
                res[i] = qs[i][1];
            else
                idx.push_back(i);
        }
        sort(begin(idx), end(idx), [&](int i, int j) { return qs[i][1] > qs[j][1]; });
        int j = heights.size() - 1;
        for (int i : idx) {
            int a = qs[i][0], b = qs[i][1];
            while (j > b) {
                while (!mono.empty() && heights[mono.back()] <= heights[j])
                    mono.pop_back();
                mono.push_back(j--);
            }
            auto it = upper_bound(rbegin(mono), rend(mono), a, [&](int i, int j){ // 從rbegin(mono)找到rend(mono) 尋找第一個讓比較條件成立的位置
                return heights[i] < heights[j];                                   // 尋找第一個其對應的 heights 值嚴格大於 heights[a] 的位置。
            });                                                                   // i 是對應容器內element的index, j 是對應傳入的 a
            res[i] = it == rend(mono) ? -1 : *it;
        }
        return res;
    }
};
