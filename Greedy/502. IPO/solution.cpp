/*
 *  1. 先把小於w的project的profit推入max heap
 *  2. 選擇pq.top() 也就是最大的profit
 *  3. 更新w 繼續step1 直到k == 0
 */
class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        int sz = profits.size();
        vector<vector<int>> m; // capital, profits
        for(auto i = 0; i < profits.size(); ++i)    // O(N)
            m.push_back({capital[i], profits[i]});
        sort(m.begin(), m.end());                   // O(NlogN)
        priority_queue<int> pq; //max-heap
        int idx = 0;
        while(k) {                                  // O(KlogN)
            while(idx < sz && w >= m[idx][0]) {
                pq.push(m[idx++][1]);
                idx++;
            }
            if(pq.empty()) break;
            w += pq.top(); pq.pop();
            k--;
        }
        return w;
    }
};
