/*  ref : https://leetcode.com/problems/minimum-score-after-removals-on-a-tree/solutions/2198204/using-dfs-c-solution-by-horcrux903-q0kc/
 *
 *  題目是要求移除兩個edge, 就會得到三個tree, 這三個tree的XOR value的最大值 - 最小值 為最小
 *
 *  題目太難了 只想到暴力破解
 *  先簡化題目 不然想破頭也想不出來
 *  如果只移除一個edge, 這樣就會有兩個tree 例如: a--b--c   d--e--f  
 *  1. 先計算total xor(a^b^c^d^e^f)
 *  2. 使用dfs往下走 cur = a,     other = total^cur
 *                   cur = a^b,   other = total^cur
 *                   cur = a^b^c, other = total^cur
 *
 *  3. 再移除一個edge就是在 a--b--c 或是 d--e--f 其中一個再切一刀　所以等於重複上面的步驟
 */
class Solution {
public:
    unordered_set<int> v[1002];
    bool vis[1002];
    int ans = INT_MAX, comp_1, comp_2, comp_3;
    int dfs(int i, vector<int> &a) {
        int curr = a[i];
        vis[i] = true;
        for (auto x : v[i])
            if (!vis[x])
                curr ^= dfs(x, a);
        return curr;
    }

    // dfs1 : 找出從cur往下的subtree的total xor
    int dfs1(int i, int j, vector<int> &a)
    {
        vis[i] = true;
        int curr = a[i];
        for (auto x : v[i]) { // 從i往下看 有幾個subtree
            if (!vis[x]) {
                int res = dfs1(x, j, a); // 算出以x開頭的subtrer xor value
                comp_2 = res;
                comp_3 = j ^ res;
                ans = min(ans, max({comp_1, comp_2, comp_3}) - min({comp_1, comp_2, comp_3}));
                curr = curr ^ res; // 加入此subtree的xor value
            }
        }
        return curr;    // 返回node i和其所有的subtree的xor value
    }

    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        for (auto x : edges) {
            v[x[0]].insert(x[1]);
            v[x[1]].insert(x[0]);
        }

        int val = 0;
        for (auto x : nums)
            val = val ^ x;

        ans = INT_MAX;
        for (auto x : edges) {
            v[x[0]].erase(x[1]);    // 移除edge x, 因為一個edge被移除了，所以tree被分為兩個
            v[x[1]].erase(x[0]);

            fill(begin(vis), end(vis), false);

            comp_1 = dfs(0, nums);  // 一個tree有包括0, 一個tree沒包刮0, 所以先從有0的開始, 算出有0的tree的xor value

            int pos;
            for (int i = 0; i < nums.size(); i++) {
                if (!vis[i]) {          // 找出第一個沒訪問過的node, 就是不包含0的另一個tree
                    pos = i;
                    dfs1(i, comp_1 ^ val, nums);    //使用dfs走訪tree, 就是在這個tree再切一刀，所以會有三個tree
                }
            }
            // 反過來 換沒包刮0的tree計算xor val
            fill(begin(vis), end(vis), false);
            comp_1 = dfs(pos, nums);
            for (int i = 0; i < nums.size(); i++) { //走訪有包括0的tree，在這個tree再切一刀
                if (!vis[i])
                    dfs1(i, comp_1 ^ val, nums);
            }

            v[x[0]].insert(x[1]);
            v[x[1]].insert(x[0]);
        }

        return ans;
    }
};
/*  用自己的理解重寫一次
 *
 */
class Solution {
    unordered_map<int, unordered_set<int>> adj;
    int ans{INT_MAX}, comp1, comp2, comp3;
    int dfs(const vector<int>& nums, vector<int>& vis, int prev, int cur) {
        int rtn = nums[cur];
        vis[cur] = 1;
        for(auto& nxt : adj[cur]) {
            if(nxt == prev) continue;
            rtn ^= dfs(nums, vis, cur, nxt);
        }
        return rtn;
    }
    int dfs2(const vector<int>& nums, vector<int>& vis, int prev, int cur, const int total) {
        int rtn = nums[cur];
        vis[cur] = 1;
        for(auto& nxt : adj[cur]) {
            if(nxt == prev || vis[nxt]) continue;
            int sub = dfs2(nums, vis, cur, nxt, total);
            comp2 = sub;
            comp3 = total ^ sub;
            ans = min(ans,
                max({comp1, comp2, comp3}) - min({comp1, comp2, comp3})
            );
            rtn ^= sub;
        }
        return rtn;
    }
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        for(auto& e : edges) {
            adj[e[0]].insert(e[1]);
            adj[e[1]].insert(e[0]);
        }
        int total{}, sz = nums.size();
        for(auto& n : nums)
            total ^= n;

        for(auto& e : edges) {
            adj[e[0]].erase(e[1]);
            adj[e[1]].erase(e[0]);

            vector<int> vis(sz);
            comp1 = dfs(nums, vis, -1, e[0]);           // 因為被edge切開了 所以e[0], e[1]分別為兩個tree的node
            dfs2(nums, vis, -1, e[1], total ^ comp1);

            fill(begin(vis), end(vis), 0);              // 使用vis避免有loop情況
            comp1 = dfs(nums, vis, -1, e[1]);
            dfs2(nums, vis, -1, e[0], total ^ comp1);

            adj[e[0]].insert(e[1]);
            adj[e[1]].insert(e[0]);
        }
        return ans;
    }
};
