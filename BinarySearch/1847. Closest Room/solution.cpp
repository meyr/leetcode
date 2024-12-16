/*  題目是找出大於等於queries[j][1] size中 id最靠近queries[j][0] 的id
 *
 *  1. 先將rooms和queries對size由大到小進行排序
 *  2. 每一個queries 將大於等於 queries[j][1] size的rooms id丟進set
 *  3. 使用binary search(upper_bound)找出最接近的id 
 *
 *  結果TLE
 */
class Solution {
    enum query_type{
        pref,
        size, 
        id
    };
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int sz = queries.size();
        vector<int> ans(sz, -1);
        for(int i = 0; i < sz; ++i) queries[i].push_back(i);
        sort(begin(queries), end(queries), [](vector<int>& a, vector<int>& b){  // size 由大到小
            return a[1] > b[1];
        });
        sort(begin(rooms), end(rooms), [](vector<int>& a, vector<int>& b){ // size 由大到小
            return a[1] > b[1];
        });
        set<int> ids;
        for(int i = 0, j = 0; i < sz; ++i) { //i-> queries, j->rooms
            if(i > 0 && queries[i][size] == queries[i - 1][size] && queries[i][pref] == queries[i - 1][pref]) {
                ans[queries[i][id]] = ans[queries[i - 1][id]];
                continue;
            }
            while(j < rooms.size() && rooms[j][1] >= queries[i][size]) {
                ids.insert(rooms[j][0]);
                j++;
            }
            if(!ids.empty()) {
                auto it = upper_bound(begin(ids), end(ids), queries[i][pref]);
                int diff = INT_MAX, id = INT_MAX;
                if(it != ids.end()) {
                    if(abs(queries[i][pref] - *it) <= diff) {
                        id = min(id, *it);
                        diff = abs(queries[i][0] - *it);
                    }
                }
                if(it != ids.begin()) {
                    if(abs(queries[i][pref] - *prev(it)) <= diff) {
                        id = min(id, *prev(it));
                        diff = abs(queries[i][pref] - *prev(it));
                    }
                }
                if(id != INT_MAX) ans[queries[i][2]] = id;
            }
        }
        return ans;
    }
};
/*  參考解答 : https://leetcode.com/problems/closest-room/solutions/1185801/c-solution-sort-the-query-by-room-size-b-xe17/
 *  想法和上面一樣卻可以通過
 */
class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        for(int i = 0; i < queries.size(); i++) queries[i].push_back(i);
        sort(queries.begin(), queries.end(), [](auto &a, auto &b) {
            return a[1] > b[1];
        });
        sort(rooms.begin(), rooms.end(), [](auto &a, auto &b){
            return a[1] > b[1];
        });
        int i = 0;
        set<int> st;
        vector<int> ans(queries.size(), -1);
        for(auto q : queries) {
            int prefer = q[0], minSize = q[1], idx = q[2];
            while(i < rooms.size() && rooms[i][1] >= minSize)
                st.insert(rooms[i++][0]);
            if(!st.empty()) {
                auto it = st.upper_bound(prefer);
                int res = it != st.end() ? abs(*it - prefer) : INT_MAX;
                int resRoomId = it != st.end() ? *it : INT_MAX;
                if(it != st.begin()) {
                    --it;
                    if(abs(*it - prefer) <= res)
                        resRoomId = *it;
                }
                ans[idx] = resRoomId;
            }
        }
        return ans;
    }
};
