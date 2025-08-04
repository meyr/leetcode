/*  因為performance = sum(speed) + min(efficiency)
 *  有兩個變數 如果可以固定effifiency 那就剩找出這個條件最大的speed
 *  
 *  1. 先把speed 和 efficiency結合
 *  2. 針對efficiency排序, 這樣就可以確定每次都拿到最小的effiency
 *  3. 使用minheap得到k-1個最大的speed, 因為第k個為最小efficiency的speed
 *
 *  time  : O(N + NlogN + NlogN) = O(NlogN)
 *  space : O(N + logN + N) = O(N)
 */
class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        int mod = 1e9 + 7;
        vector<pair<int, int>> vp{};  // efficiency, speed
        for(int i = 0; i < n; ++i)
            vp.push_back({efficiency[i], speed[i]});
        sort(begin(vp), end(vp), [](auto& a, auto& b){
            if(a.first > b.first) return true;
            else if(a.first == b.first) return a.second > b.second;
            else return false;
        });
        priority_queue<int, vector<int>, greater<>> minheap{}; // speed
        long long sum{}, ans{};
        for(auto& [eff, spd] : vp) {
            sum += spd;
            minheap.push(spd);
            ans = max(ans, sum * eff);
            if(minheap.size() == k) {
                sum -= minheap.top();
                minheap.pop();
            }
        }
        return ans % mod;
    }
};
