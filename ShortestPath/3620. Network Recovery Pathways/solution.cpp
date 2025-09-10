/*   參考 : https://leetcode.com/problems/network-recovery-pathways/solutions/6980177/no-bs-by-votrubac-mzu5/
 *  
 *   這邊刪除的策略是關鍵。
 *   因為我們有兩個變數，score(越大越好), total cost(<= k 這邊算越小越好，因為可以走更遠)
 *   所以我們的greedy point是 score 越大，total cost越小
 *
 *   當m[j].insert({s, p}) 插入之後得到的iterator it 當中，map會先根據score排序，再來才是根據total cost排序
 *   it前面一定是socre比較小的，和我們的greedy point越大越好相違背，如果total cost又比較大，當然是刪除。  --> line 16, 17(strategy I)
 *                             socore比較小，但是total cost也比目前小的情況不刪除，因為有可能走的可以更遠
 *   it後面一定是score大於等於目前的值，如果後面的total cost又比目前的小，表示條件比你好，哪就是刪掉自己 --> line 21 (strategy III)
 *                                                         比目前的還大，表示目前的可以走更遠，那就加入maxheap試看看 --> line 19 (strategy II)    
*/
class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        vector<map<long long, long long>> m(online.size()); // 根據每個node有個map<score, path>
        vector<vector<array<long long, 2>>> al(online.size());
        for (const auto &e : edges)
            if (online[e[0]] && online[e[1]])
                al[e[0]].push_back({e[1], e[2]});
        priority_queue<array<long long, 3>> pq; // maxheap, 因為我們要找出最大的score
        pq.push({INT_MAX, 0, 0});
        while (!pq.empty() && pq.top()[2] != online.size() - 1) {   // 第一個到達sz - 1就是答案, 因為是maxheap
            auto [score, path, i] = pq.top(); pq.pop(); // score : 目前valid path的最小code, path : total cost, i : current node
            for (auto [j, cost] : al[i])
                if (auto s = min(cost, score), p = path + cost; p <= k) { // s : next score, p : next total cost
                    auto it = m[j].insert({s, p}).first;                 // pair<iterator,bool>
                    while (it != begin(m[j]) && prev(it)->second >= it->second) // strategy I 
                        m[j].erase(prev(it));
                    if (next(it) == end(m[j]) || next(it)->second > it->second)
                        pq.push({s, p, j});                                     // strategy II
                    else
                        m[j].erase(it);                                         // strategy III
                }
        }
        return pq.empty() ? -1 : pq.top()[0];
    }
};
/*------------------------------------------------------------------------------------------------------------------------------------------------ */
/*
 *  另一種解法是使用binary search 
 *  因為限制從node 0走道node sz - 1只有total cost <= k
 *  但是我們又必須統計 每個valid path上的最小cost
 *
 *  min cost : 1, 2, 3, 4, 5, 6, 7     如果限制min cost的值, 等於限制了是否可以走到終點 min cost越大越有機會走到終點
 *  reach end: x, x, x, x, o, o, o
 */
