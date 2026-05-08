/*  參考解答: https://leetcode.com/problems/minimum-jumps-to-reach-end-via-prime-teleportation/solutions/7009825/easy-c-solution-using-dijkstra-with-intu-esuo/
 *
 *  重點是找出 每個prime可以跳過去的nums[i]
 *  然後使用shortest path algorithm來找出到達終點的最短dist
 *
 */
class Solution {
public:
    // 因數分解，例如 x = 12 = 2^2 * 3
    //                  res = [2, 3]
    //               x = 30 = 2 * 3 * 5 --> 2 * 15 --> 2 * 3 * 5
    //                  res = [2, 3, 5]
    //               x = 13(prime)
    //                  res = [13]
    //
    //  回傳的res裡面的member都是prime
    vector<int> factor(int x) {
        vector<int> res;
        for(int d = 2; d * d <= x; d++){ // d = 2, 3, 4, 5, 6, ...sqrt(x)
            if(x % d == 0) {             // x不是prime, 表示有因數
                res.push_back(d);
                while(x % d == 0)  // 一直除直到因數沒有了
                    x /= d;
            }
        }
        if(x > 1)
            res.push_back(x);
        return res;
    }
    int minJumps(vector<int>& nums) {
        unordered_map<int, vector<int>> adj;
        int n = nums.size();
        for(int i = 0; i < n; i++)
            for(const auto& it : factor(nums[i]))
                adj[it].push_back(i);

        vector<int> dist(n, INT_MAX);
        priority_queue<pair<int, int>,vector<pair<int, int>>, greater<pair<int, int>>> q; //minheap, <dist, index>
        q.push({0, 0});
        dist[0] = 0;

        while(!q.empty()){
            auto [dis,node]=q.top(); q.pop();
            adj[nums[node]].push_back(node + 1);
            adj[nums[node]].push_back(node - 1);
            for(const auto& nxt : adj[nums[node]]) {
                if(nxt >= 0 && nxt < n && dist[nxt] > dis + 1) {
                    dist[nxt] = dis + 1;
                    q.push({dist[nxt], nxt});
                }
            }
            adj[nums[node]].clear(); // why clean? 路徑只能用一次? 為什麼題目沒寫
        }
        return dist.back();
    }
};
/*  2026/05/08 daily challenge TLE
 *
 *  重點在建立挑轉的關係
 *  1. prime可以跳到 nums[j] % p == 0 的位置, 也就是質數的倍數位置, 既然是質數的倍數所以一定不是質數
 *  2. 數字都可以分解成質數相乘 所以只要確認可以從那個質數跳過來即可
 *  3. vector<int> factor(int x) 對x進行因數分解 如果本身是因數   res = {x}
 *                                                       不是因數 res = {p1, p2, p3...} 裡面不會有1是因為 1不是prime
 */

