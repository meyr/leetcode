/*
 *    我的想法是每個node都建立左右child node上來的depth
 *    每個querie都被設為0 因為被移除掉了 然後往上直到root就可以知道目前的depth
 *    這個想法TLE 但是還是記錄起來
 *
 *                        5(3, 2)
 *           8 (2, 1)                    9(1, 1)
 *  2 (1, 1)     1 (0, 0)         3(0, 0)    7(0, 0)  
 * 4(0,0) 6(0,0)
 *
 */
class Solution {
    unordered_map<int, pair<int, int>> child;
    unordered_map<int, pair<int, int>> parent;
    enum dir {
        left,
        right
    };
    int rv;
    int dfs(TreeNode* root) {
        if(!root) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        child[root->val] = make_pair(l, r);
        if(root->left) parent[root->left->val] = make_pair(root->val, left);
        if(root->right) parent[root->right->val] = make_pair(root->val, right);
        return max(l, r) + 1;
    }
    int check(int val, int d, int newval) {
        auto [l, r] = child[val];
        newval = max(newval, d == left ? r : l);
        if(val == rv) {
            return newval;
        } else {
            auto [np, nd] = parent[val];
            return check(np, nd, newval + 1);
        }
    }
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        dfs(root);
        rv = root->val;
        vector<int> ans;
        for(auto& q : queries) {
            int p = parent[q].first;
            int d = parent[q].second;
            ans.push_back(check(p, d, 0));
        }
        return ans;
    }
};
/*
 *  參考 : https://leetcode.com/problems/height-of-binary-tree-after-subtree-removal-queries/solutions/2758013/level-depth/
 *  
 *   
 *
 */ 
class Solution {
    unordered_map<int, int> level, depth;
    int d1[100001], d2[100001];            // __important__ 紀錄相同level中最大和第二大depth的數目
                                           // 因為如果移除的是第一大則depth會變成第二大
                                           //     如果移除的是第二大以後則depth不變
    int traverse(TreeNode* n, int l = 0) {
        if(!n) return 0;
        // level為此node向上的depth
        // depth為此node向下的depth
        level[n->val] = l;
        int d = depth[n->val] = 1 + max(traverse(n->left, l + 1),
                                traverse(n->right, l + 1));
        if(d1[l] < d) {
            d2[l] = d1[l];
            d1[l] = d;
        } else if(d2[l] < d)
            d2[l] = d;
        return d;
    }
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        traverse(root, 0);
        transform(begin(queries), end(queries), begin(queries), [&](int q){
            int l = level[q];
            int d = depth[q];
            return l + (d1[l] == d ? d2[l] : d1[l]) - 1; // -1 是因為level和depth會計算兩次node
        });
        return queries;
    }
};
