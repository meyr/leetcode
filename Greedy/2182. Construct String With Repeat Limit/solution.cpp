/*  因為要建立lexicographically larger string
 *  所以先統計char從最大的開始取
 *  超過repeatLimit就取下一個char放在中間
 *
 *  time  : O(N) , N : sizeof s
 *  space : O(N)
 */
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> cnt(26);
        for(auto& c : s) cnt[c - 'a']++;
        string rtn{};
        for(int i = 25; i >= 0; --i) {
            if(cnt[i] == 0) continue;
            if(cnt[i] > repeatLimit) {
                int j = i - 1;
                while(j >= 0 && cnt[j] == 0) --j;
                if(j >= 0) {
                    rtn += string(repeatLimit, i + 'a') + string(1, j + 'a');
                    cnt[i] -= repeatLimit;
                    i++;
                    cnt[j] -= 1;
                } else {
                    rtn += string(repeatLimit, i + 'a');
                }
            } else {
                rtn += string(cnt[i], i + 'a');
            }
        }
        return rtn;
    }
};
/*  另一種想法是先把lexicographically larger string建立出來
 *  如果有char重複repeatLimit就和下一個char交換
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        vector<int> cnt(26);
        for(auto& c : s) cnt[c - 'a']++;
        string rtn{};
        for(int i = 25; i >= 0; --i) rtn += string(cnt[i], i + 'a');
        int i{1}, cur{1}, j{};
        for(; i < rtn.size(); ++i) {
            cur = rtn[i] == rtn[i - 1] ? cur + 1 : 1;
            if(cur > repeatLimit) {
                j = max(j, i + 1); // __important__ 繼續往下找
                while(j < rtn.size() && rtn[i] == rtn[j]) ++j;
                if(j == rtn.size()) break;
                else {
                    swap(rtn[i], rtn[j]);
                    cur = 1;
                }
            }
        }
        return i == rtn.size() ? rtn : rtn.substr(0, i);
    }
};
/*  使用priority_queue取出下一個char
 *
 */
class Solution {
public:
    string repeatLimitedString(string s, int repeatLimit) {
        unordered_map<char, int> m;
        for(auto& c : s) m[c]++;
        priority_queue<char> q;
        for(auto& ref : m) q.push(ref.first);
        string ans{};
        while(!q.empty()) {
            char c = q.top(); q.pop();
            int cnt = min(m[c], repeatLimit);
            m[c] -= cnt;
            ans += string(cnt, c);
            if(m[c] > 0) {
                if(q.empty()) break;
                ans.push_back(q.top());
                m[q.top()]--;
                if(m[q.top()] == 0) q.pop();
                q.push(c);
            }
        }
        return ans;
    }
};
