/*
 *   參考解答 : https://leetcode.com/problems/valid-parenthesis-string/solutions/4985287/c-friendly-interview-solution-using-stack-good-explanation-and-example/
 *
 *   使用兩個stack分別記錄left和star
 *   這樣才有辦法判斷left和star是否成對
 *
 *   time  : O(N)
 *   space : O(N)
 */
class Solution {
public:
    bool checkValidString(string s) {
        stack<int> star, left;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '(') left.push(i);
            else if(s[i] == '*') star.push(i);
            else {
                if(left.empty() && star.empty()) return false;
                else if(!left.empty()) left.pop();
                else star.pop();
            }
        }
        while(!left.empty()) {
            if(star.empty()) return false;// 沒有star可以和left配對
            if(left.top() > star.top()) return false; // star在left前面
            star.pop();
            left.pop();
        }
        return true;
    }
};
