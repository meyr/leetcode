/*
 *  因為只有四種可能 00, 25, 50, 75 所以針對這四種可能找到最小的解
 * 
 *  time  : O(N)
 *  space : O(1) 
 */

class Solution {
    int find(string& num, int st, char target) {
        int idx = st;
        while(idx >= 0 && num[idx] != target) idx--;
        return idx >= 0 ? st - idx : num.size();
    }
public:
    int minimumOperations(string num) {
        int sz = num.size();
        if(sz == 1) return num[0] == '0' ? 0 : 1;
        int ans = sz;
        int zero = find(num, sz - 1, '0'); // 先找出zero的位置 需要刪除多少數字 
        int five = find(num, sz - 1, '5'); // 先找出five的位置
        if(sz - zero - 2 >= 0)
            ans = min({ans, zero + find(num, sz - zero - 2, '0'), // 如果找到zero就繼續襖0或是5
                            zero + find(num, sz - zero - 2, '5'),
                            sz - 1});							  // 刪除除了0以外的數字也是一個解
        if(sz - five - 2 >= 0)
            ans = min({ans, five + find(num, sz - five - 2, '2'),
                           five + find(num, sz - five - 2, '7')});
        return ans;
    }
};
