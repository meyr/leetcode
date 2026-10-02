/*  一開始以為這是recursive的問題 寫了以下的解答 結果錯了
 *
 *  n = 4, 會少了 "(())(())"  因為 少考慮 n = 2 + n = 2情況
 *  n > 4 會有更多情況沒考慮到 所以不能這樣寫
 */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        if(n == 1) return {"()"};
        else {
            vector<string> prev = generateParenthesis(n - 1);
            unordered_set<string> rtn;
            for(auto& str : prev) {
                rtn.insert("()" + str);
                rtn.insert(str + "()");
                rtn.insert("(" + str + ")");
            }
            return vector<string>(begin(rtn), end(rtn));
        }
    }
};
/*
 *  使用最笨的方法列舉全部可能 在檢查哪一個是valid parenthese
 *  helper()根據left, right建立parenthese string
 *  check():
 *           '(' : 1, ')' : -1 --> 從左到右計算balance數值
 *           1. 數值要 >= 0
 *           2. 最後要 == 0
 *
 */
class Solution {
    void helper(int left, int right, string cur, vector<string>& rtn)
    {
        if(left == 0 && right == 0)
            rtn.push_back(cur);
        else {
            if(left)
                helper(left - 1, right, cur + "(", rtn);
            if(right)
                helper(left, right - 1, cur + ")", rtn);
        }
    }

    bool check(const string& str)
    {
        int bal{};
        for(auto& c : str) {
            bal += c == '(' ? 1 : -1;
            if(bal < 0) return false;
        }
        return bal == 0;
    }

public:
    vector<string> generateParenthesis(int n) {
        vector<string> rtn, ans;
        string cur;
        helper(n, n, cur, rtn);
        for(const auto& str : rtn)
            if(check(str))
                ans.push_back(str);
        return ans;
    }
};
/*
 *  check可以跟helper合併 邊產生parentheses邊檢查正確性
 *  time  : O(2^N)
 *  space : O(2^N)
 */
class Solution {
    void helper(int left, int right, int bal, string& cur, vector<string>& rtn)
    {
        if(left == 0 && right == 0 && bal == 0)
            rtn.push_back(cur);
        else {
            if(left) {
                cur.push_back('(');
                helper(left - 1, right, bal + 1, cur, rtn); // 直接在這邊計算balance少一個變數
                cur.pop_back();
            }
            if(right && bal > 0) {                          // 如果添加')'必須保證bal是大於0, 避免負值
                cur.push_back(')');
                helper(left, right - 1, bal - 1, cur, rtn);
                cur.pop_back();
            }
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> rtn;
        string cur{};
        helper(n, n, 0, cur, rtn);

        return rtn;
    }
};
/*
 *      2026/10/2 daily challenge
 *
 *      因為只有兩種可能 所以兩種可能都去試 再去判斷是否為正確就可以
 *      少了很多檢查條件
 *
 *      time  : O(2^N) 因為兩種都會嘗試
 *      space : O(2^N)
 */
class Solution {
    int n;
    void helper(int rem, int val, string& ans, vector<string>& rtn) {
        if(rem < 0 || val < 0) return;
        if(ans.size() == n * 2) {
            rtn.push_back(ans);
            return;
        } else {
            ans.push_back('(');
            helper(rem - 1, val + 1, ans, rtn);
            ans.pop_back();
            ans.push_back(')');
            helper(rem, val - 1, ans, rtn);
            ans.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> rtn;
        string ans;
        this->n = n;
        helper(n, 0, ans, rtn);
        return rtn;
    }
};
