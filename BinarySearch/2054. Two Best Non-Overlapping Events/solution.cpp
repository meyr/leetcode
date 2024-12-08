/*
 *   題目指要求參加最多兩個meeting，既然要得到最大的sum所以最好是參加兩個
 *   所以先參加一個 然後從可以參加的list中 選最大的那一個
 *
 *   time  : O(NlogN + N + NlogN) = O(NlogN)
 *   space : O(N + logN) = O(N)
 */
class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int sz = events.size();
        sort(begin(events), end(events)); // O(NlogN)
        vector<int> maxp(sz + 1);
        maxp[sz - 1] = events[sz - 1][2];
        for(int j = sz - 2; j >= 0; --j) // O(N)
            maxp[j] = max(maxp[j + 1], events[j][2]);
        int ans{};
        for(int i = 0; i < sz; ++i) { // O(NlogN)
            vector<int> target{events[i][1] + 1, 0, 0};
            auto nextidx = lower_bound(begin(events) + i, end(events), target) - 
                events.begin();
            ans = max(ans, events[i][2] + maxp[nextidx]);
        }
        return ans;
    }
};
/*
 *   Greedy point :  紀錄目前看到non-overlap的最大值  
 * 
 *   time  : O(NlogN + NlogN) = O(NlogN)
 *   space : O(N)
 */
 class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int sz = events.size();
        if(sz == 1) return events[0][2];
        priority_queue<vector<int>> pq; // maxheap, {結束時間, value}
        int maxv{}, ans{}; // 目前最大val
        sort(begin(events), end(events));
        for(auto& e : events) {
            while(!pq.empty() && -pq.top()[0] < e[0]) {
                maxv = max(maxv, pq.top()[1]);
                pq.pop();
            }
            ans = max(ans, e[2] + maxv);
            pq.push({-e[1], e[2]});
        }
        return ans;
    }
};
