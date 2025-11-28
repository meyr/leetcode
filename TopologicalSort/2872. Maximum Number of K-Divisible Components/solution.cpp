/*
    參考: https://leetcode.com/problems/maximum-number-of-k-divisible-components/solutions/6156598/maximum-number-of-k-divisible-components-ibji/

    Sum of values is divisible by k. --> __important__ 表示切下一個subtree剩下的也是k的倍數
    因為 0 <= values[i] <= 1e9 所以有機會overflow必須使用long
*/
class Solution {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k) {
        // special case不須計算
        if(n < 2) return 1;

        unordered_map<int, vector<int>> m;
        vector<int> ind(n);
        for(const auto& e : edges) {
            m[e[0]].push_back(e[1]);
            m[e[1]].push_back(e[0]);
            ind[e[0]]++;
            ind[e[1]]++;
        }
        vector<long> longValue(begin(values), end(values));
        queue<int> q;
        for(int i = 0; i < n; ++i) {
            if(ind[i] == 1)
                q.push(i);
        }
        int ans{};
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            long addValue{};                // __important__ 如果可以整除k就切下來
            if(longValue[cur] % k == 0)     //               不行就把結果往鄰近node累加
                ans++;                      //
            else addValue = longValue[cur]; //
            for(const auto& nxt : m[cur]) {
                if(ind[nxt] == 0) continue;
                longValue[nxt] += addValue;
                if(--ind[nxt] == 1)
                    q.push(nxt);
            }
        }
        return ans;
    }
};
/*  2025/11/28 daily challenge 還是沒做出來
 *  題目有提示 "Sum of values is divisible by k" 這是寫在Constraints有點奸詐 因為有時候沒往下拉看
 *  既然 sum(values) 為 k 的部數 所以我切下來的subtree為k的倍數 剩下的subtree也為k的倍數
 *  而且題目要求最多數目的subtree 所以遇到k的倍數就切下來 不行就把累積的數值繼續往其他地方推
 */
