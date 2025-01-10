/*  因為universal的定義是在words2裡面的 string 都要出現 所以每個char出現的次數取最大值
 *
 *  time  : O(N + M), N : total chars in words1, M : total chars in words2
 *  space : O(N)
 */

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        unordered_map<char, int> m2;
        for(const auto& word : words2) {
            unordered_map<char, int> m;
            for(const auto& c : word) {
                m[c]++;
                m2[c] = max(m2[c], m[c]);
            }
        }
        vector<string> rtn;
        for(const auto& word : words1) {
            int cnt = m2.size();
            unordered_map<char, int> m;
            for(const auto& c : word) {
                m[c]++;
                if(m2.count(c) && m[c] == m2[c]) cnt--;
            }
            if(cnt == 0)
                rtn.push_back(word);
        }
        return rtn;
    }
};
/* 使用array<int, 26>取代unordered_map<char, int>
 *
 */
class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        array<int, 26> m2{};
        for(const auto& word : words2) {
            array<int, 26> m{};
            for(auto& c : word) {
                m2[c - 'a'] = max(m2[c - 'a'], ++m[c - 'a']);
            }
        }
        int cnt{};
        for(auto& ref : m2) cnt += ref != 0;
        vector<string> rtn;
        for(auto& word : words1) {
            array<int, 26> m{};
            int _cnt = cnt;
            for(auto& c : word) {
                if(++m[c - 'a'] == m2[c - 'a'])
                    _cnt--;
            }
            if(!_cnt)
                rtn.push_back(word);
        }
        return rtn;
    }
};
