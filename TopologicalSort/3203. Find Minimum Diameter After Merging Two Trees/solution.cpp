/*  __我搞錯diameter的定義導致寫出來怪怪的__ ==> 先弄清楚題目再作答
 *
 *  參考 : https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/solutions/5389938/find-diameter-by-votrubac-ny3m/
 *
 *  The diameter of a tree is the length of the longest path between any two nodes in the tree.
 *  diameter : 任意兩個node之間的距離"最長的"稱為diameter
 * 
 *  所以是Max(dist(i, j)), dist(i, j) : 計算node i和node j的距離
 *  假設從i到j長的如下 因為是最長的 所以找不到比這個還長的path 通常i 和 j為leaf node 才會有最長的path
 *
 *  i--a--b--c--d--e--f--j
 *
 *  所以使用topologic sort從leaf開始往內推, 每個node維持一個最大depth值表示從leaf推過來最長的距離
 *
 *  i--a--b--c--d--e--f--j
 *  0  1  2  3  3  2  1  0
 *           *  *
 *
 *  當推到鄰近點 例如: node c下一個是node d, 則depth[c] + depth[d] + 1 即為目前的distance
 *  diameter = max(diameter, depth[c] + depth[d] + 1); // 就可以找出diameter
 *
 *
 *  當找出diameter之後 從root往node i或是node j 的距離是 diameter / 2 或是 (diameter + 1) / 2 端看diameter是奇數還是偶數
 *
 *  i--a--b--r--c--e--j  diameter = 6, dist(r, i) = 3, dist(r, j) = 3, diameter / 2 = 3, (diameter + 1) / 2 = 3
 *  i--a--b--r--c--j     diameter = 5, dist(r, i) = 3, dist(r, j) = 2, diameter / 2 = 2, (diameter + 1) / 2 = 3
 *
 *  所以兩個graph連在一起後 max(d1/2,(di+1)/2) + max(d2/2, (d2+1)/2) + 1 (因為(d1+1)/2 一定大於 d1/2)= (d1+1)/2 + (d2+1)/2 + 1(連接兩個graph的距離)
 *  考慮到連結後成為一個grapy有可能 對方diameter太短 還是連回自己的比較長 如下 1-2-3-r1-6-5-4還是比較長
 *
 *  1--2--3--r1------r2--a 
 *  4--5--6--|        |--b
 *
 *  所以 res = max({d1, d2, (d1+1)/2 + (d2+1)/2 + 1});
 */

class Solution {
public:
    int diameter(vector<vector<int>>& edges) {
        int m = edges.size() + 1, res = 0;
        vector<vector<int>> al(m);
        vector<int> degree(m), depth(m), vis(m);
        queue<int> q;
        for (const auto &e : edges) {
            al[e[0]].push_back(e[1]);
            al[e[1]].push_back(e[0]);
        }
        for (int i = 0; i < m; ++i)
            if ((degree[i] = al[i].size()) == 1)
                q.push(i);
        while (!q.empty()) {
            int i = q.front(); q.pop();
            vis[i] = true;                  // 表示已經訪問過了
            for (int j : al[i]) {
                if (--degree[j] == 1)
                    q.push(j);
                if (!vis[j]) {
                    res = max(res, depth[j] + depth[i] + 1);    // 找出diameter of edges
                    depth[j] = max(depth[j], depth[i] + 1);     // depth往沒訪問過的node推
                }
            }
        }
        return res;
    }
    int minimumDiameterAfterMerge(vector<vector<int>>& e1, vector<vector<int>>& e2) {
        auto d1 = diameter(e1), d2 = diameter(e2);
        return max({d1, d2, (d1 + 1) / 2 + (d2 + 1) / 2 + 1}); // 最長diameter有可能出現在edge1或是edge2或是從edge1連接到edge2
    }
};
