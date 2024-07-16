/*
 *  怎麼寫都寫不好
 *  所以參考解答
 *
 */
class Solution {
    bool find(TreeNode *root, int val, string& path) {
        if(!root) return false;
        if(root->val == val) return true;
        bool rtn = false;
        if(find(root->left, val, path)) { // 可以在left找到val所以在path上加上'L'
            path.push_back('L');
            rtn = true;
        }
        if(find(root->right, val, path)) {// 可以在right找到val所以在path上加上'R'
            path.push_back('R');
            rtn = true;
        }
        return rtn;
    }
public:
    string getDirections(TreeNode* root, int startValue, int destValue) {
        string sp, dp;
        find(root, startValue, sp); // 從root到startValue的路徑
        find(root, destValue, dp);  // 從root到destValue的路徑
        while(!sp.empty() && !dp.empty() && sp.back() == dp.back()) { // 從root開始的相同路徑必須丟掉
            sp.pop_back();
            dp.pop_back();
        }
        return string(sp.size(), 'U') + string(dp.rbegin(), dp.rend());
    }
};
