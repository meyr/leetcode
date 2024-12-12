/*  一開始的想法是把全部的數值都推到minheap
 *  然後再一個一個拿出來計算 就可以得到最大答案
 *
 *  time  : O(MNlog(MN) + MNlog(MN))
 *  space : O(MN)
 */
class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        priority_queue<long long, vector<long long>, greater<>> pq; //minheap
        for(auto& shop : values)
            for(auto& v : shop) pq.push(v);
        long long ans{};
        long long d = 1;
        while(!pq.empty()) {
            ans += pq.top() * d++;
            pq.pop();
        }
        return ans;
    }
};
/*  上面的TC會被minheap的大小所控制
 *  所以減少minheap的大小就可以降低TC
 *
 *  這次使用tuple只把每個shop的最後一個值放進去
 *
 *  time  : O(MlogM + MNlogM) = O(MNlogM)
 *  space : O(M)
 */
class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        int m = values.size(), n = values[0].size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq; // minheap <value, y, x>
        for(int y = 0; y < m; ++y)  // O(MlogM)
            pq.push({values[y].back(), y, n - 1});
        long long ans{};
        int d{1};
        while(!pq.empty()) {    // O(MNlogM)
            auto [v, y, x] = pq.top(); pq.pop();
            ans += v * (long long)d++;
            if(x > 0)
                pq.emplace(values[y][x - 1], y , x - 1);
        }
        return ans;
    }
};
/*   因為 m <= 10 乾脆不要使用minheap
 *   使用idx來紀錄每個shop最後的index
 *
 *   time  : O(MNM)
 *   space : O(M)
 */
class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        int m = values.size(), n = values[0].size();
        vector<int> idx(m, n);
        int cnt = m * n, d{1};
        long long ans{};
        while(cnt--) {
            int t = 0;
            while(t < m && idx[t] == 0) t++;
            for(int y = t + 1; y < m; ++y)
                if(idx[y] > 0 && values[y][idx[y] - 1] < values[t][idx[t] - 1])
                    t = y;
            ans += values[t][idx[t] - 1] * (long long)d;
            d++;
            idx[t]--;
        }
        return ans;
    }
};
