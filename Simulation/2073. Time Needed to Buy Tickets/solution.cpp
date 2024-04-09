/*
 * 因為長度很少 所以可以用brust force一個一個減 但是效率不好
 *
 *
 *  參考答案 : https://leetcode.com/problems/time-needed-to-buy-tickets/solutions/1576932/c-one-pass/
 *
 *  __思考一開始和最後的vector差異 可以得到不同的想法__
 *
 *  一開始是  [2, 3, 2]
 *           -[2, 2, 2] 所以答案就是累加減少的這個vector
 *  最後會變成[0, 1, 0] 
 *
 *  其中 tickets[k] - (i > k) 是因為 i 如果再 k後面會少減一次
 *  因為 tickets[k] 已經變成0了，不需要往後。
 *
 *  time  : O(N)
 *  space : O(1)
 */

class Solution {
public:
    int timeRequiredToBuy(vector<int>& tickets, int k) {
        int ans{};
        for(int i = 0; i < tickets.size(); ++i)
            ans += min(tickets[k] - (i > k), tickets[i]);
        return ans;
    }
};
