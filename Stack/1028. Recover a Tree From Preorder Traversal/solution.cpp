/*  參考解答:
 *  https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/solutions/274605/c-iterative-stack-by-votrubac-fnll/
 */
 class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        stack<TreeNode*> st;
        for(auto p = 0, len = 0, level = 0; p < S.size(); p += len) {
            level = len = 0;
            while(S[p] == '-') ++level, ++p; // 找出第一個數字開頭, level計算前面有幾個'-'
            while(p + len < S.size() && S[p + len] != '-') ++len; // 找出數字長度
            TreeNode *n = new TreeNode(stoi(S.substr(p, len)));
            while(st.size() > level) st.pop(); // 表示右邊的child node
            if(!st.empty()) {
                if(st.top()->left == nullptr) st.top()->left = n;
                else st.top()->right = n;
            }
            st.push(n);
        }
        while(st.size() > 1) st.pop();
        return st.top();
    }
};
