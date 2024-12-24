/* 
 * Greedy point : 使用minheap從快腐敗的apple先吃
 * 
 * 因為超過days.size()後處理不好 所以先用暴力破解
 *
 */
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;//minheap, <rot of day, apples>
        int ans{};
        for(int i = 0; i < apples.size() || !pq.empty(); ++i) {
            if(i < apples.size() && apples[i] != 0)
                pq.push({i + 1 + days[i], apples[i]});
            while(!pq.empty() && pq.top()[0] <= i + 1) pq.pop();
            if(!pq.empty()) {
                vector<int> cur = pq.top(); pq.pop();
                if(--cur[1] > 0) pq.push(cur);
                ans++;
            }
        }
        return ans;
    }
};
/*  參考 :  https://leetcode.cn/problems/maximum-number-of-eaten-apples/solutions/1172766/chi-ping-guo-de-zui-da-shu-mu-by-leetcod-93ka/
 *
 *  重點是把吃掉的apples加到天數去 表示之後還是可以從那些空白天數先吃
 */
class Solution {
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<>> pq; //minheap, <rot of day, apples>
        int ans{};
        for(int d = 0; d < apples.size(); ++d) {
            if(apples[d] > 0)
                pq.push(make_pair(days[d] + d + 1, apples[d]));
            while(!pq.empty() && pq.top().first <= d + 1) pq.pop();
            if(!pq.empty()) {
                auto [rod, cnt] = pq.top(); pq.pop();
                if(--cnt > 0) pq.push(make_pair(rod, cnt));
                ans++;
            }
        }
        int prev = apples.size() + 1;
        while(!pq.empty()) {
            while(!pq.empty() && pq.top().first <= prev) pq.pop(); // 先把rotten apples丟掉
            if(pq.empty()) break;
            auto [rod, cnt] = pq.top(); pq.pop();
            int eatten = min(rod - prev, cnt);
            ans += eatten;
            prev += eatten;  // __important__ 不是 prev = rod, 而是 prev += eatten; 表示有吃apple才佔天數
        }
        return ans;
    }
};
