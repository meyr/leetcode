/*
 *  time  : O(NM + MlogM) , N : size of votes, M : soze of votes[0]
 *  space : O(MN + logM) = O(MN)
 */
class Solution {
public:
    string rankTeams(vector<string>& votes) {
        if(votes.size() == 1) return votes.front();
        vector<vector<int>> st(26, vector<int>(votes.front().size()));
        for(auto& vote : votes) {
            for(int i = 0; i < vote.size(); ++i) {
                st[vote[i] - 'A'][i]++;
            }
        }
        string rtn = votes.front();
        sort(begin(rtn), end(rtn), [&](char a, char b){
            a -= 'A', b -= 'A';
            if(st[a] > st[b]) return true;
            else if(st[a] == st[b]) return a < b;
            else return false;
        });
        return rtn;
    }
};
