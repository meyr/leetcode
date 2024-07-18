/*
 *  類似 2096. Step-By-Step Directions From a Binary Tree Node to Another
 *  先找出root到leaf的走法 因為要找出最近的距離 所以跳掉兩個node重複的path
 *
 *  time  : O(N + M^2), N : number of nodes. M : number of leaf nodes
 *  space : O(N + M)
 */
class Solution {
    vector<string> leaf; // O(M)
    void helper(TreeNode* root, string& path) {
        if(!root->left && !root->right) // 儲存leaf node的path
            leaf.push_back(path);
        else {
            if(root->left) {
                path += 'L';
                helper(root->left, path);
                path.pop_back();
            }
            if(root->right) {
                path += 'R';
                helper(root->right, path);
                path.pop_back();
            }
        }
    }
public:
    int countPairs(TreeNode* root, int distance) {
        string path{};
        helper(root, path); // 紀錄所有從root到leaf node的路徑
        int ans{};
        for(int i = 0; i < leaf.size(); ++i) {
            for(int j = i + 1; j < leaf.size(); ++j) {
                int k = 0;
                while(k < leaf[i].size() && k < leaf[j].size() && leaf[i][k] == leaf[j][k]) // 跳過相同的路徑
                    k++;
                if(leaf[i].size() - k + leaf[j].size() - k <= distance) // 剩下的字串和就是最短路徑
                    ans++;
            }
        }
        return ans;
    }
};
