/*  參考 : https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/solutions/1328953/c-solution-dijkstras-algorithm-by-invuln-6gu2/
 *
 *  這題寫出了一個TLE 問題在於他有兩個限制maxTime和passingFees
 *                    所以只有一個條件有改善(moveTime or passing fees) 就必須放進minheap
 *
 */
class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        int n = passingFees.size();
        vector<int> minFees(n, INT_MAX), minTimes(n, INT_MAX);
        minFees[0] = passingFees[0];
        minTimes[0] = 0;
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq; // minheap, <fees, time, node>
        pq.push({minFees[0], 0, 0});
        unordered_map<int, vector<vector<int>>> um;
        for(auto& e : edges) {
            um[e[0]].push_back({e[1], e[2]});
            um[e[1]].push_back({e[0], e[2]});
        }
        while(!pq.empty()) {
            vector<int> _vec = pq.top(); pq.pop();
            int fee = _vec[0], time = _vec[1], cur = _vec[2];
            if(cur == n - 1) return fee;
            for(auto& _vec : um[cur]) {
                int nxt = _vec[0], moveTime = _vec[1];
                if(time + moveTime <= maxTime) {
                    if(fee + passingFees[nxt] < minFees[nxt]) {     // 過路費變少
                        minFees[nxt] = fee + passingFees[nxt];
                        pq.push({minFees[nxt], time + moveTime, nxt});
                    }
                    else if(time + moveTime < minTimes[nxt]) {      // 過路費沒變少 --> 走其他路過來, 但是時間變短了, 因為時間變短有機會走其他路 所以也要列入考慮
                        minTimes[nxt] = time + moveTime;
                        pq.push({fee + passingFees[nxt], minTimes[nxt], nxt});
                    }
                }
            }

        }
        return -1;
    }
};
