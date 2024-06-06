/*
 *   使用map來看使否有滿足條件
 *
 *   time  : O(NlogN)
 *   space : O(N)
 */

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if(hand.size() % groupSize != 0) return false;
        if(groupSize == 1) return true;
        map<int, int> m;
        for(auto& n : hand) m[n]++; // O(NlogN)
        while(!m.empty()) { // O(NlogN)
            int cur = m.begin()->first;
            if(--m[cur] == 0) m.erase(cur);
            int sz = groupSize - 1;
            while(sz--) {
                if(!m.count(++cur)) return false;
                if(--m[cur] == 0) m.erase(cur);
            }
        }
        return true;
    }
};
