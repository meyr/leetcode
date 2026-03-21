/*  使用pair<char, int>來統計重複的char
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    string removeDuplicates(string s, int k) {
        vector<pair<char, int>> vp;
        for(auto& c : s) {
            if(vp.empty() || c != vp.back().first) vp.push_back({c, 1});
            else if(++vp.back().second == k)
                vp.pop_back();
        }
        string rtn{};
        for(auto& p : vp)
            rtn += string(p.second, p.first);
        return rtn;
    }
};
