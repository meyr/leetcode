/*  一開始針對events排序怎樣都會有錯誤的情況
 *  這樣做的缺點是有些情況考慮不到
 *  ex : 1, 2
 *       1, 2
 *       1, 5
 *       1, 5
 *       3, 3  <-- 其實要中間加入
 */
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(begin(events), end(events));
        int ans{1}, cur = events[0][0] + 1;
        for(int i = 1; i < events.size(); ++i) {
            if(cur >= events[i][0] && cur <= events[i][1]) {
                ans++;
                cur++;
            } else if(cur < events[i][0]) {
                ans++;
                cur = events[i][0] + 1;
            }
        }
        return ans;
    }
};
/*  參考: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/solutions/510263/javacpython-priority-queue-by-lee215-2054/
 *
 *  掃描可以參加的日子 cur = 1, ..., 1e5
 *
 *  Greedy point : 把可以參加的event放入minheap, 之後只選擇__最早結束的__event參加
 *
 *  這個作法等於二次排序 先對startDay排序 再用minheap對endDay排序
 *
 *  time  : O(NlogN + KlogN) = O(KlogN)
 *  space : O(N + logN) = O(N)
 */
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        priority_queue<int, vector<int>, greater<>> minheap;
        sort(begin(events), end(events));
        int ans{};
        for(int cur = 1, i = 0; cur <= 1e5; ++cur) {
            while(!minheap.empty() and minheap.top() < cur) minheap.pop();
            while(i < events.size() && cur >= events[i][0]) {
                minheap.push(events[i][1]);
                i++;
            }
            if(!minheap.empty()) {
                minheap.pop();
                ans++;
            }
        }
        return ans;
    }
};
