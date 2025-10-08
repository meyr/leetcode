/*
 *  time  : O(MlogM + NlogM) = O((N+M)logM)
 *  space : O(logM + N)
 */
class Solution {
public:
    vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
        int m = potions.size();
        sort(begin(potions), end(potions)); // O(MlogM)
        vector<int> rtn;
        for(const auto& spell : spells) {  // O(NlogM)
            auto need = (success + spell - 1) / spell;
            if(need < potions.front()) rtn.push_back(m);
            else if(need > potions.back()) rtn.push_back(0);
            else {
                auto it = lower_bound(begin(potions), end(potions), need);
                rtn.push_back(end(potions) - it);
            }
        }
        return rtn;
    }
};
