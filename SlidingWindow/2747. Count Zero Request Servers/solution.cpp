/*
 *      使用slinding window來統計queries interval內收到訊息的server數量
 *
 *      time  : O(NlogN + MlogM)
 *      space : O(N + M)
 */
class Solution {
    enum logsData{
        sid, stime
    };
    enum queriesData{
        itv, idx
    };
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(begin(logs), end(logs), [](auto& a, auto& b){
            return a[stime] < b[stime];
        });
        int sz = queries.size();
        vector<vector<int>> q;
        for(int i = 0; i < sz; ++i)
            q.push_back({queries[i], i});
        sort(begin(q), end(q), [](auto& a, auto& b){
            return a[itv] < b[itv];
        });
        vector<int> ans(sz);
        unordered_map<int, int> ump;
        for(int i = 0, right = 0, left = 0; i < sz; ++i) {
            int pos = q[i][idx];
            int ed = q[i][itv];
            int st = ed - x;
            while(right < logs.size() && ed >= logs[right][stime]) {
                ump[logs[right][sid]]++;
                right++;
            }
            while(left < logs.size() && st > logs[left][stime]) {
                if(ump[logs[left][sid]] == 1) ump.erase(logs[left][sid]);
                else ump[logs[left][sid]]--;
                left++;
            }
            ans[pos] = n - ump.size();
        }
        return ans;
    }
};
