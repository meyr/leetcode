/*    參考解答
 *
 *    原本的思路是先找出最大cost path然後再一路一路往上，但是就卡住了
 *    其實一路一路往上就是post-order，必須先知道left和right
 *    
 *    比較left和right的差異，把差異加入ans
 *    並且傳回cost最大的路徑值
 */

class Solution {
    int n, ans;
    int helper(vector<int>& cost, int idx) {
        if(idx > n) return 0;
        int l = helper(cost, idx * 2);
        int r = helper(cost, idx * 2 + 1);
        if(l == r) return cost[idx - 1] + l; // 不須增減，回傳最大cost的路徑值
        else {
            ans += max(l, r) - min(l, r);    // 因為l和r不一樣，需要補
            return cost[idx - 1] + max(l, r);// 回傳最大cost的路徑值
        }
    }
public:
    int minIncrements(int n, vector<int>& cost) {
        this->n = n;
        helper(cost, 1);
        return ans;
	// time  : O(N), 每個node都會拜訪兩次
	// space : O(log2(N)), 因為resursive的stack 
    }
};
