/*
 *    參考答案: https://leetcode.com/problems/greatest-common-divisor-traversal/solutions/3568567/union-find-in-c-java-and-python/
 *    
 *    這題要找出可以跳到每個node就想到union find，只要連在一起就可以跳過去
 *    但是容易寫出O(N^2)的解答。
 *    for(int i = 0; i < sz; ++i)
 *        for(int j = i + 1; j < sz; ++j)
 *            if(gcd(nums[i], nums[j]) > 1) uf.un(i, j);
 *
 *    考慮nums[i] 可以跟誰連結? 例如nums[i] = 2 * 2 * 3 * 5;        
 *    表示可以和index < i 且prime factor有2, 3, 5的數字
 *    使用unordered_map<int, int> have，來儲存prime factor的最後index，只需要存最後的因為之前的已經連結再一起了。
 */

class UnionFind{
    vector<int> root, rank;
public:
    UnionFind(int n) : root(n), rank(n, 1) {
        iota(begin(root), end(root), 0);
    }
    int find(int x) {
        return root[x] == x ? x : root[x] = find(root[x]);
    }
    int un(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return 0;
        if(rank[a] < rank[b]) swap(a, b);
        root[b] = a;
        return rank[a] += rank[b];
    }
    int getRank(int n) {
        return rank[find(n)];
    }
};
class Solution {
public:
    bool canTraverseAllPairs(vector<int>& nums) {
        const int n = nums.size();
        if (n == 1) return true;
        UnionFind uf(n);
        unordered_map<int, int> have;
        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            if (x == 1) return false; // 因為1的prime factor為1，達不到任何node
            for (int d = 2; d * d <= x; ++d) { // 從2開始找prime factor
                if(x % d != 0) continue;
                if (have.count(d))   // 找到一個prime factor，且之前也有，進行連結
                    uf.un(i, have[d]);
                have[d] = i;         // 設定此prime factor為index i
                while (x % d == 0)   // 跳過相同的prime factor
                    x /= d;
            }
            if (x > 1) { // 最後一個prime factor
                if (have.count(x))
                    uf.un(i, have[x]);
                have[x] = i;
            }
        }
        return uf.getRank(0) == n;
    }
};
