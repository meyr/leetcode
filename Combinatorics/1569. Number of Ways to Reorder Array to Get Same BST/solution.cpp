/*
 *      參考官方答案 : https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/solutions/3505954/number-of-ways-to-reorder-array-to-get-s-t95p/
 *
 *      給你一個array nums希望你從這個array重建BST(Binary Search Tree) 並且回傳多少種的排列組合 可以建構出相同的BST
 *
 *      首先怎麼從array建構一個BST?
 *      1. 從一個empty BST開始
 *      2. 從array依序取出數字放入BST內 取完全部數字就完成BST
 *      3. 取一個數字後和root相比 比較小就放入left child tree, 否則放入right child tree
 *      4. 如果有child tree就繼續和child tree root相比 依此類推
 *
 *      例如 [3, 1, 2, 4, 5]
 *      1. 先取3, 因為empty BST 所以是
 *
 *              3
 *
 *      2. 再取1
 *
 *              3
 *             /
 *            1
 *
 *      3. 再取 2
 *
 *              3
 *             /
 *            1
 *             \
 *              2
 *
 *      4. 再取4
 *
 *              3
 *             / \
 *            1   4
 *             \
 *              2
 *
 *      5. 再取5
 *
 *              3
 *             / \
 *            1   4
 *             \   \
 *              2   5
 *
 *
 *     也就是先和root比較決定出left, right 之後剩下的空間內只要left和right順序不變就可以
 *     以下是我寫的解答 但是錯了
 *
 *     因為當sub array 例如 [3, 5, 4] 就會有兩種情況 [3, 5, 4]或是[3, 4, 5]也是可以組成相同的BST
 */
class Solution {
    long long helper(const vector<int>& left, const vector<int>& right, int i, int j) {
        if(i == left.size() && j == right.size()) return 1;
        else if(i == left.size()) return helper(left, right, i, j + 1);
        else if(j == right.size()) return helper(left, right, i + 1, j);
        else return helper(left, right, i + 1, j) + helper(left, right, i, j + 1);
    }
public:
    int numOfWays(vector<int>& nums) {
        int r = nums[0];
        vector<int> left, right;
        for(int i = 1; i < nums.size(); ++i)
            if(nums[i] > r) right.push_back(nums[i]);
            else left.push_back(nums[i]);
        return (helper(left, right, 0, 0) % (long long)(1e9 + 7)) - 1;
    }
};

/*
 *      參考官方答案 : https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/solutions/3505954/number-of-ways-to-reorder-array-to-get-s-t95p/
 *
 *      根據上面的討論 必須先計算出每個subarray的排列數 dfs(left array) * dfs(right array) 最後再乘上其中一個array在剩下的位置的排列數 C(sz - 1, sz of sub array)
 *      上面個解答只有算出後面那一項 沒考慮到每個subarray的排列數
 */
class Solution {
public:
    int numOfWays(vector<int>& nums) {
        int m = nums.size();
        // Table of Pascal's triangle
        table.resize(m + 1);
        for(int i = 0; i < m + 1; ++i) {
            table[i] = vector<long long>(i + 1, 1);
            for(int j = 1; j < i; ++j) {
                table[i][j] = (table[i - 1][j - 1] + table[i - 1][j]) % mod;
            }
        }

        return (dfs(nums) - 1) % mod;
    }

private:
    vector<vector<long long>> table;
    long long mod = 1e9 + 7;

    long long dfs(vector<int> &nums){
        int m = nums.size();
        if(m < 3) {
            return 1;
        }

        vector<int> leftNodes, rightNodes;
        for(int i = 1; i < m; ++i){
            if (nums[i] < nums[0]) {
                leftNodes.push_back(nums[i]);
            } else {
                rightNodes.push_back(nums[i]);
            }
        }

        long long leftWays = dfs(leftNodes) % mod;
        long long rightWays = dfs(rightNodes) % mod;

        return (((leftWays * rightWays) % mod) * table[m - 1][leftNodes.size()]) % mod;
    }
};
