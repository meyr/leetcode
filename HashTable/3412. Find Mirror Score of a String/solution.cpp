/*
 *   mirror 的意思是兩個加起來會等於219
 *
 *   a(97), z(122) = 219
 *   b(98), y(121)
 *
 *   time  : O(N)
 *   space : O(N)
 */
class Solution {
public:
    long long calculateScore(string s) {
        unordered_map<char, vector<int>> m;
        long long ans{};
        for(int i = 0; i < s.size(); ++i) {
            char target = 219 - s[i];
            if(m[target].size()) {
                ans += (i - m[target].back());
                m[target].pop_back();
            } else
                m[s[i]].push_back(i);
        }
        return ans;
    }
};
