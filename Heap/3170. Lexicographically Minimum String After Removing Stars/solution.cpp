/*
 *  問題變成遇到'*'就移除看過的char中最小的
 *  如果一樣就是index最大的 這樣才會是 lexicographically smallest
 *
 *  time : O(NlogN + N)
 *  space: O(N)
 */

class Solution {
public:
    string clearStars(string s) {
        unordered_set<int> del;
        auto cmp = [](auto& a, auto& b){
            if(a.first > b.first) return true;
            else if(a.first == b.first) return a.second < b.second;
            else return false;
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> pq(cmp);
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '*') {
                auto [c, idx] = pq.top(); pq.pop();
                del.insert(idx);
            } else
                pq.push(make_pair(s[i], i));
        }
        string rtn;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '*' || del.count(i)) continue;
            rtn.push_back(s[i]);
        }
        return rtn;
    }
};
