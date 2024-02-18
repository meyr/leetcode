/*
    2024/2/18 自己寫怎麼寫都怪怪的，大致上的邏輯都對，就是缺了一點
              所以參考了解答。

              一定會有一個heap來紀錄最先結束的meeting room
              再使用另一個heap來記錄avaliable meeting room，因為我們需要取數字最小的

*/

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<int> room(n);
        using plli = pair<long long, int>;
        priority_queue<int, vector<int>, greater<int>> unused; // room num
        priority_queue<plli, vector<plli>, greater<plli>> pq; // end time, room num
        sort(begin(meetings), end(meetings));
        for(int i = 0; i < n; ++i) unused.push(i);
        for(auto& m : meetings) {
            int s = m[0], e = m[1];
            // 把已經結束的meeting room回收
            while(!pq.empty() && pq.top().first <= s) {
                unused.push(pq.top().second);
                pq.pop();
            }
            // 如果有unused就直接取用
            if(!unused.empty()) {
                room[unused.top()]++;
                pq.push(make_pair(e, unused.top()));
                unused.pop();
            // 沒有meeting room，就必須等待到第一個結束
            // 所以直接從pq取用第一個，並加上時間後，再推回pq
            } else {
                auto [endTime, num] = pq.top(); pq.pop();
                room[num]++;
                endTime += (e - s);
                pq.push(make_pair(endTime, num));
            }
        }
        // 找出使用率最高的房間index
        return max_element(begin(room), end(room)) - begin(room);
    }
};
