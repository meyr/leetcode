/* 參考解答 : https://leetcode.com/problems/cousins-in-binary-tree-ii/solutions/3420081/level-sum/
 *
 * 一開始一直糾結在要使用level transversal 一次完成 但是這樣寫出來的答案太複雜
 * 只要使用兩次DFS就可以簡單的寫出答案
 * 1. 第一次先計算每個的level sum
 * 2. 第二次update node value但是扣掉silbing node sum
 *
 * time  : O(N)
 * space : O(N)
 */
class Solution {
    vector<int> lsum; // level sum
    void level_sum(TreeNode* n, int d) {
        if(!n) return;
        lsum.resize(max((int)lsum.size(), d + 1));  // 這邊如果使用 if(lsum.size() == d) lsum.push_back(0) 會TLE
                                                    // 使用resize就會過
        lsum[d] += n->val;
        level_sum(n->left, d + 1);
        level_sum(n->right, d + 1);
    }
    void update_sum(TreeNode* n, int sum, int d) {
        if(!n) return;
        n->val = lsum[d] - sum;
        sum = n->left ? n->left->val : 0;
        sum += n->right ? n->right->val : 0;
        update_sum(n->left, sum, d + 1);
        update_sum(n->right, sum, d + 1);
    }
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        level_sum(root, 0);
        update_sum(root, root->val, 0);
        return root;
    }
};
/**
 *  使用level order transversal
 *  計算出level sum之後必須保留node來update child sum
 *
 *  time  : O(N)
 *  space : O(N) 
 */
class Solution {
public:
    TreeNode* replaceValueInTree(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        root->val = 0;
        while(!q.empty()) {
            vector<TreeNode*> buf;  // 保留node後續update sum使用
            int sum{};
            for(int loop = q.size(); loop > 0; --loop) {
                TreeNode* n = q.front(); q.pop();
                if(n->left) q.push(n->left), sum += n->left->val;
                if(n->right) q.push(n->right), sum += n->right->val;
                buf.push_back(n);
            }
            for(auto& n : buf) {
                int val = n->left ? n->left->val : 0;   // 計算silbing sum
                val += n->right ? n->right->val : 0;
                if(n->left) n->left->val = sum - val;
                if(n->right) n->right->val = sum - val;
            }
        }
        return root;
    }
};
