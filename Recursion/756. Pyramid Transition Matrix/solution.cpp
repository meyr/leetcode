/*
 *  想法是一層一層突破 
 *  先收集allowed的pattern
 *  再把每一層的所有可能 string收集起來 一個一個測試
 *  結果是TLE
 *
 *  time  : O(N^2 * 2^N)
 *
 */
class Solution {
    unordered_map<string, vector<char>> um;
    void helper2(vector<vector<char>> pattern, vector<string>& bottoms, string& cur, int i) {
        if(i == pattern.size()) bottoms.push_back(cur);
        else {
            for(auto& c : pattern[i]) {
                cur.push_back(c);
                helper2(pattern, bottoms, cur, i + 1);
                cur.pop_back();
            }
        }
    }
    bool helper(string& bottom) {
        if(bottom.size() == 1) return true;
        vector<vector<char>> pattern;
        int total{1};
        for(int i = 0; i < bottom.size() - 1; ++i) {
            string base = bottom.substr(i, 2);
            if(!um.count(base)) return false;
            else {
                pattern.push_back(um[base]);
                total *= um[base].size();
            }
        }
        vector<string> bottoms;
        string cur{};
        helper2(pattern, bottoms, cur, 0);
        for(auto& b : bottoms)
            if(helper(b)) return true;
        return false;
    }
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for(auto& p : allowed)
            um[p.substr(0, 2)].push_back(p[2]);
        return helper(bottom);
    }
};
/* ref : https://leetcode.com/problems/pyramid-transition-matrix/solutions/621275/c-dfs-by-votrubac-6z11/
 * 
 * 想法類似但是解法更精簡
 *
 */
class Solution {
    unordered_map<string, vector<char>> m;
public:
    bool dfs(string &bottom, string top) {
        if (top.size() == bottom.size() - 1)    // 收集到了top
            return top.empty() ? true : dfs(top, string());
        for (auto ch : m[bottom.substr(top.size(), 2)]) // 從top size可以推到目前的substring 然後加上每個char
            if (dfs(bottom, top + ch))
                return true;
        return false;
    }
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (auto &s : allowed)
            m[s.substr(0, 2)].push_back(s[2]);
        return dfs(bottom, string());
    }
};
/* ref : https://leetcode.cn/problems/pyramid-transition-matrix/solutions/3866474/tu-jie-hui-su-vis-you-hua-pythonjavacgo-9kcb9/
 * 參考上面的解答 加上visited來減少重複檢查
 */
class Solution {
    unordered_map<string, vector<char>> um;
    unordered_set<string> visited;              // 加上visited避免重複檢查
    bool helper(string& bottom, string top) {
        if(visited.count(top)) return false;
        if(top.size() == bottom.size() - 1) {
            if(bottom.size() == 1) return true;
            visited.insert(bottom);                 // bottom已經檢查過了 所以加入
            return helper(top, string());
        }
        for(auto& c : um[bottom.substr(top.size(), 2)])
            if(helper(bottom, top + c)) return true;
        return false;
    }
public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for(auto& p : allowed)
            um[p.substr(0, 2)].push_back(p[2]);
        return helper(bottom, string());
    }
};
/* ref : https://leetcode.cn/problems/pyramid-transition-matrix/solutions/3866474/tu-jie-hui-su-vis-you-hua-pythonjavacgo-9kcb9/
 * 參考同上的解答 因為傳遞string比較浪費時間
 * 可以使用int來編碼 'A'~'F' --> 1 ~ 6, 0: 保留表示none避免無法分辨 AA, 和AAA 這類狀況
 * 因為 A = 0100 0001
 *      B = 0100 0010
 *      C = 0100 0011
 *      D = 0100 0100
 *      E = 0100 0101
 *      F = 0100 0110
 *
 *      Z = 0101 1010
 *   mask =    1 1111    只需要mask = 2^5 - 1 = 31來當mask就可以截出 'A'~'Z' 得到 1 ~ 26
 *
 *   且 bottom.length <= 6 只需 6*3 = 18 bits, 所以可以用一個int來編碼 bottom的狀態 
 * 
 *   |--- --- --- --- --- --- ........ |  32 bits
 *
 *   使用int來編碼 就可以使用以下的code來換不同char 把第j個清掉 並且換上top
 *   ```cpp
 *   pyramid[i] &= ~(7 << (j * 3)); // 清除之前填的字母，等价于 pyramid[i][j] = 0
 *   pyramid[i] |= top << (j * 3); // 等价于 pyramid[i][j] = top
 *   ```
 *
 */
