/*
 *   類似678. Valid Parenthesis String 只是locked[i] == '0' 為 '*'
 *
 */

class Solution {
public:
    bool canBeValid(string s, string locked) {
        stack<int> star, left;
        for(int i = 0; i < s.size(); ++i) {
            if(locked[i] == '0') star.push(i);
            else if(s[i] == '(') left.push(i);
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
        return star.size() % 2 == 0;
    }
};
