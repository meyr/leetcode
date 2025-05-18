/*  參考 : https://leetcode.cn/problems/painting-a-grid-with-three-different-colors/solutions/870045/yong-san-chong-bu-tong-yan-se-wei-wang-g-7nb2/
 * 
 *  矩陣大小是m x n 可以看成每一個column一個column往右塗過去 因為 1<= m <= 5  
 *  列舉所有狀態[0, pow(3, m)) 來看看這些數字中那些相鄰是不相同的color --> unordered_map<int, vector<int>> valid
 *  列舉每個狀態可以有的相鄰color --> unordered_map<int, vector<int>> adj
 *  
 *  當n = 1, 表示我們可以塗的顏色就是valid中的顏色 所以f[mask] = 1
 *  當n = 2, 表示我們可以有的組合是n = 1時所有的總和
 *
 *  time  : O(N*3^M)
 *  space : O(3^2M)
 */
class Solution {
public:
    int colorTheGrid(int m, int n) {
        // 列舉所有正確的color排列
        unordered_map<int, vector<int>> valid; // 儲存vector<int>是因為等等要比較相鄰的顏色是否相同
        for(int val = 0; val < pow(3, m); ++val) {
            vector<int> color;
            int _val = val;
            for(int i = 0; i < m; ++i) {
                color.push_back(_val % 3);
                _val /= 3;
            }
            bool isValid = true;
            for(int i = 1; i < m; ++i)
               if(color[i] == color[i - 1]) {
                    isValid = false;
                    break;
               }
            if(isValid)
                valid[val] = color;
        }
        // 列舉所有 color vector旁邊可以使用的color vector
        unordered_map<int, vector<int>> adj; 
        for(auto& [val1, color1] : valid) {
            for(auto& [val2, color2] : valid) {
                if(val1 == val2) continue;
                bool isValid = true;
                for(int i = 0; i < m; ++i) {
                    if(color1[i] == color2[i]) {
                        isValid = false;
                        break;
                    }
                }
                if(isValid)
                    adj[val1].push_back(val2);
            }
        }
        // 計算每行可以排列的數量
        vector<int> f(pow(3, m));
        for(auto& ref : valid)
            f[ref.first] = 1;
        while(--n) {
            vector<int> g(pow(3, m));
            for(auto& [val, color] : valid)
                for(auto& nxt : adj[val])
                    g[val] = (g[val] + f[nxt]) % (int)(1e9 + 7);
            f = move(g);
        }
        return accumulate(begin(f), end(f), 0LL) % (int)(1e9 + 7);
    }
};
