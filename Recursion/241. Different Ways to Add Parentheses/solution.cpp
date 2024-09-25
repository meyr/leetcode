/*
 * 參考 : https://leetcode.com/problems/different-ways-to-add-parentheses/solutions/66328/a-recursive-java-solution-284-ms/ 
 * 遇到每個operator(+/-/*) 就可以把expression切成前後兩半進行recursion
 */
class Solution {
public:
    vector<int> diffWaysToCompute(const string& expression) {
        vector<int> rtn;
        for(int i = 0; i < expression.size(); ++i) {
            const char& c = expression[i];
            if(c == '-' || c == '*' || c == '+') {
                for(auto& n : diffWaysToCompute(expression.substr(0, i))) { // 這邊直接傳入lvalue 所以必須宣告成 const string&
                    for(auto& m : diffWaysToCompute(expression.substr(i + 1))) {
                        switch(c) {
                            case '+' : rtn.push_back(n + m); break;
                            case '-' : rtn.push_back(n - m); break;
                            case '*' : rtn.push_back(n * m); break;
                        }
                    }
                }
            }
        }
        if(rtn.size() == 0) // special case 沒有任何的operator 也就是只有數字
            rtn.push_back(stoi(expression));
        return rtn;
    }
};
/*
    2*3-4*5
    (2*3)-4*5   -->  6-4*5 --> (6-4)*5, 6-(4*5) --> 10, -14
    (2*3-4)*5   -->  [2, -2] * 5 --> 10, -10
    2*(3-4)*5   -->  2* -1 * 5 --> -10, -10
    2*(3-4*5)   -->  2*[-5, -17] --> -10, -34
    2*3-(4*5)   -->  2*3-20 --> -14, -34
*/
