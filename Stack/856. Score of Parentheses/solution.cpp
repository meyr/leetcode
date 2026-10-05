/*
 *      模擬題目的意思 使用兩個vector來代表stack
 *      每遇到'('就把index和分數0 push進去
 *      當遇到')'就看看index是否是前一個 是的話就是1分 把它加入上一層的stack
 *                          如果不是前一個表示是(A) 那就是把分數乘上2再加入上一層
 *
 *      time  : O(N)
 *      space : O(2*N) = O(N)
 */
class Solution {
public:
    int scoreOfParentheses(string s) {
        vector<int> pos{-1}, score{0};
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '(') {
                pos.push_back(i);
                score.push_back(0);
            } else {
                if(pos.back() + 1 == i) {
                    score.pop_back();
                    score.back() += 1;
                } else {
                    int sc = score.back(); score.pop_back();
                    score.back() += 2 * sc;
                }
                pos.pop_back();
            }
        }
        return score[0];
    }
};
