/*  
 *  參考 : https://leetcode.cn/problems/minimum-number-of-refueling-stops/solutions/1636921/zui-di-jia-you-ci-shu-by-leetcode-soluti-nmga/
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    int minRefuelStops(int target, int fuel, vector<vector<int>>& st) {
        // special case
        if(fuel >= target) return 0; // 目前的fuel就可以到達終點
        else if(st.empty() || fuel < st[0][0]) return -1; // 目前的油到不了終點 而且沒有加油站 或是 目前的油到不了第一個加油站

        priority_queue<int> pq;    // 遇到加油站中 每個加油站的油量
        st.push_back({target, 0}); // 把target視為最後一個station 因為路程也需要耗油
        int ans{}, prev = 0, idx{};
        for(; idx < st.size(); ++idx) {
            fuel -= st[idx][0] - prev;  // ___important___ 每到一個station就必須使用的油量

            while(fuel < 0 && !pq.empty()) { // 如果油量不足到此station 從以前經過的statoin中選一個最大的
                fuel += pq.top();
                pq.pop();
                ans++;
            }

            if(fuel < 0) return -1; // 即使加了油還是到不了
            prev = st[idx][0];
            pq.push(st[idx][1]);
        }

        return idx == st.size() && fuel >= 0 ? ans : -1;
    }
};
