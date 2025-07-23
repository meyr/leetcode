/*
 *  參考解答 : https://leetcode.com/problems/maximum-score-from-removing-substrings/solutions/5464043/explanations-no-one-will-give-you-2-detailed-approaches-extremely-simple-and-effective/
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int removePairs(string &s, string t) {
        int idx = 0, count = 0; // 使用idx直接在s裡面操作
        for (char c : s) {
            s[idx++] = c;
            if (idx > 1 && s[idx - 1] == t[1] && s[idx - 2] == t[0]) {
                count++;
                idx -= 2;
            }
        }
        s.resize(idx);
        return count;
    }

    int maximumGain(string s, int x, int y) {
        int res = 0;
        vector<string> p{"ab", "ba"};

        if (y > x) {    // x always greater than y
            swap(p[0], p[1]);
            swap(x, y);
        } 

        res += removePairs(s, p[0]) * x;
        res += removePairs(s, p[1]) * y;
        return res;
    }
};
/* 2025/07/23 daily challenge
 * 
 * 一開始看到maximum score所以直覺想用DP, 但是寫起來太奇怪了
 * 所以改用greedy 的作法
 *
 * 因為要maximum score所以一定是先對分數大的先取, 例如"ab"(x=5), 再取"ba"(y=4)
 * 所以要先判斷是那個pattern分數比較高
 *
 * 使用do{}while()是因為我本來是想說取完第二個pattern之後 是否有可能前一個pattern又可以取
 *
 */
class Solution {
    vector<string> pattern{"ab", "ba"};
public:
    int maximumGain(string s, int x, int y) {
        if(y > x) {
            swap(x, y);
            swap(pattern[0], pattern[1]);
        }
        int ans{}, _ans{}, idx{}, cnt{};
        vector<int> score{x, y};
        do{
            ans = _ans;
            string tmp{};
            string& p = pattern[idx];
            for(auto& c : s) {
                if(!tmp.empty() && tmp.back() == p[0] && c == p[1]) {
                    _ans += score[idx];
                    tmp.pop_back();
                } else
                    tmp.push_back(c);
            }
            idx = (idx + 1) % 2;
            s = move(tmp);
            if(ans == _ans) cnt++;
            else cnt = 0;
        } while(cnt < 2);

        return ans;
    }
};
/*  參考: https://leetcode.com/problems/maximum-score-from-removing-substrings/solutions/1009578/c-greedy-stack-by-votrubac-46ze/
 *  和自己寫的概念一樣 只需要做兩次即可
 */
class Solution {
    vector<string> pattern{"ab", "ba"};
    string helper(const string& s, const int sc, const string& p) {
        string rtn{};
        for(auto& c : s) {
            if(!rtn.empty() && rtn.back() == p[0] && c == p[1])
                rtn.pop_back();
            else
                rtn.push_back(c);
        }
        return rtn;
    }
public:
    int maximumGain(string s, int x, int y) {
        if(y > x) {
            swap(x, y);
            swap(pattern[0], pattern[1]);
        }
        string s1 = helper(s, x, pattern[0]);
        string s2 = helper(s1, y, pattern[1]);
        return (s.size() - s1.size()) / 2 * x + (s1.size() - s2.size()) / 2 * y;
    }
};
