/*  參考:
 *  https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/solutions/1190222/can-jia-hui-yi-de-zui-duo-yuan-gong-shu-u8e8u/
 *
 *  因為每一個人都會有favorite所以最後一定會走進loop
 *
 *  case 1
 *  node x 走到後來會進入loop, loop length = 2  則整條路徑都可以坐入circle, 且loop == 2都可以進入會議
 *                                              (joinable += len[i] + len[favorite[i]];)
 *                                              所以每個loop = 2選擇最長的路徑
 *                                              怎麼選擇最長路徑? 因為loop == 2所以只有兩個node
 *                                              只需要把len[i] + len[favorite[i]] 即可
 *                                              且j = favorite[i], len[j] = max(len[j], len[i] + 1); 
 *                                              所以len[j]為最長路徑。
 *
 *  case 2
 *                             loop length >= 3 則只有loop可以坐入circle，只能有一組loop >= 3進入會議
 *
 *  ans = max(loop >= 3 node size, sum(loop == 2 node size));
 *                    ans                  joinable
 *
 *  Topological sort : 一層一層撥，直到cyclic components
 *  disjoint union : 找出cyclic graph的長度
 *
 */
class Solution {
    vector<int> root, rank;
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(int a, int b) {
        a = find(a), b = find(b);
        if(a == b) return 0;
        if(rank[a] < rank[b]) swap(a, b);
        root[b] = a;
        return rank[a] += rank[b];
    }
public:
    int maximumInvitations(vector<int>& favorite) {
        int sz = favorite.size();
        root.resize(sz), rank.resize(sz, 1);
        iota(begin(root), end(root), 0);

        // use topological sort to get cyclics and length of chains
        vector<int> ind(sz), len(sz, 1); // len : 統計從最旁邊的node到此點的長度
        for(int i = 0; i < sz; ++i)
            ind[favorite[i]]++;
        queue<int> q;
        for(int i = 0; i < sz; ++i)
            if(ind[i] == 0) q.push(i);
        while(!q.empty()) {
            int n = q.front(); q.pop();
            int f = favorite[n];
            len[f] = max(len[f], len[n] + 1);  // __important__ 只取最長的路徑
            if(--ind[f] == 0) q.push(f);
        }

        // use disjoint set to get the length of cyclics
        for(int i = 0; i < sz; ++i) { // 如果ind[i] 不為0表示為loop
            if(ind[i] != 0) un(i, favorite[i]);
        }

        // get the maximum ans
        int ans{}, joinable{};
        for(int i = 0; i < sz; ++i) {
            if(ind[i] == 0) continue; // we only focus on cyclics
            if(rank[find(i)] == 2) { // the length of cyclic == 2, could join to table
                ind[favorite[i]]--; // 因為loop == 2所以另一個點只要ind[favorite[i]]-- 就會等於0 下次就不會檢查
                joinable += len[i] + len[favorite[i]];
            } else
                ans = max(ans, rank[find(i)]); // the len  of cyclic >= 3, form a table by themself
        }
        return max(ans, joinable);
    }
};
