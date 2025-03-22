/*
 *  參考解答
 *  這邊要先搞懂complete connected components
 *  就是在一個group裡面每個node都有一個edge可以通到其他node
 *  所以全部的edges = n * (n - 1) / 2, n為node個數
 * 
 *  使用union find的時候順便統計這個group的edge個數
 */
class Solution {
    vector<int> root, rank, count;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        count[x]++; // 先把這個edge連接到x
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        count[x] += count[y];       // 把y全部edge加到x裡面
        return rank[x] += rank[y];
    }
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        root.resize(n);
        rank.resize(n, 1);
        count.resize(n);
        iota(begin(root), end(root), 0);
        for(auto& edge : edges)
            un(edge[0], edge[1]);
        int ans{};
        for(int i = 0; i < n; ++i) {
            int r = find(i);
            if(rank[r] * (rank[r] - 1) / 2 == count[r]) {   // 檢查是否有滿足的group
                ans++;
                count[r] = 0;   // 清掉count of edge避免下次遇到又成立
            }
        }
        return ans;
    }
};
