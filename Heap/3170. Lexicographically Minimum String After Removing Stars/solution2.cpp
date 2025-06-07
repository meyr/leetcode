/*
    參考解答 使用2d vector來紀錄
*/
class Solution {
public:
    string clearStars(string s) {
        vector<vector<int>> cnt(26, vector<int>());
        int sidx = 'z';
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '*') {
                while(sidx <= 'z' and cnt[sidx].empty()) sidx++;
                if(sidx <= 'z') {
                    s[cnt[sidx].back()] = '*';
                    cnt[sidx].pop_back();
                }
            } else {
                sidx = min(sidx, s[i] - 'a');
                cnt[s[i] - 'a'].push_back(i);
            }
        }
        string rtn{};
        for(int i = 0; i < s.size(); ++i)
            if(s[i] != '*')
                rtn += s[i];
        return rtn;
    }
};
