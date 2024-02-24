/*     
 *     參考答案: https://leetcode.com/problems/find-all-people-with-secret/solutions/1599815/c-union-find/
 *    
 *     這題的重點是，時間一樣的時候，怎麼找出目前的group和person 0是否有連結
 *     先把時間t內連結起來，如果沒有和person 0連結再一起，再進行reset
 *     union find的reset就是把root[x] = x，再把root設為原本
 *     因為有reset，rank不在適用。
 */
class UnionFind {
    vector<int> root, rank;
public:
    UnionFind(int n) : root(n), rank(n, 1) {
        iota(begin(root), end(root), 0);
    }
    int connect(int a, int b) {
       //a = find(a), b = find(b);
       //if(a == b) return 0;
       //if(rank[a] > rank[b]) {
       //    root[b] = a;
       //    return rank[a] += rank[b];
       //} else {
       //    root[a] = b;
       //    return rank[b] += rank[a];
       //}
       
       // rank因為右reset不在適用，直接connect即可
       root[find(a)] = find(b);

    }
    int find(int a) {
        if(root[a] == a) return a;
        else return root[a] = find(root[a]);
    }
    bool isConnected(int a, int b) {
        return find(a) == find(b);
    }
    void reset(int a) { root[a] = a; }
};
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& A, int firstPerson) {
        int sz = A.size();
        sort(begin(A), end(A), [](auto &a, auto &b) { 
            return a[2] < b[2]; 
        }); // Sort the meetings in ascending order of meeting time
        UnionFind uf(n);
        uf.connect(0, firstPerson); // Connect person 0 with the first person
        for (int i = 0; i < sz; ) {
            vector<int> ppl;
            int time = A[i][2];
            for (; i < sz && A[i][2] == time; ++i) { // For all the meetings happening at the same time
                uf.connect(A[i][0], A[i][1]); // Connect the two persons
                ppl.push_back(A[i][0]); // Add both persons into the pool
                ppl.push_back(A[i][1]);
            }
            for (int n : ppl) { // For each person in the pool, check if he/she's connected with person 0.
                if (!uf.isConnected(0, n)) 
                    uf.reset(n); // If not, this person doesn't have secret, reset it.
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (uf.isConnected(0, i)) 
                ans.push_back(i); // Push all the persons who are connected with person 0 into answer array
        }
        return ans;
    }
};
