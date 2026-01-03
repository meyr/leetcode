/*  參考解答
 *
 */
class Solution {
public:
    int numOfWays(int n) {
        // 1. 先找出1x3所有可能的排列
        unordered_map<int, vector<int>> valid;
        for(int c = 0; c < pow(3, 3); ++c) {
            vector<int> color;
            int cc = c;
            for(int loop = 0; loop < 3; ++loop) {
                color.push_back(cc % 3);
                cc /= 3;
            }
            if(color[0] == color[1] || color[1] == color[2]) continue; // 相鄰顏色一樣
            valid[c] = color;
        }
        // 2. 找出一個1x3的grid他下面可以接那些1x3 grid
        unordered_map<int, vector<int>> adj;
        for(auto& [val1, color1] : valid) {
            for(auto& [val2, color2] : valid) {
                // 和上面顏色一樣
                if(color1[0] == color2[0] || color1[1] == color2[1] || color1[2] == color2[2]) continue;
                adj[val1].push_back(val2);
            }
        }
        // 3. 第一層(f)從valid來取得
        vector<int> f(pow(3, 3));
        for(auto& [val, _] : valid)
            f[val] = 1;
        // 4. 第二層(g)以後從 valid和adj計算得來
        while(--n) {
            vector<int> g(pow(3, 3));
            for(auto& [val, _] : valid) {
                for(auto& nxt : adj[val])
                    g[val] = (g[val] + f[nxt]) % (int)(1e9 + 7);
            }
            f = move(g);
        }
        return accumulate(begin(f), end(f), 0LL) % (int)(1e9 + 7);
    }
};
