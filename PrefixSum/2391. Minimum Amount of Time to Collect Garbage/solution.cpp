/*
 *    收集所有的垃圾 sum of all char
 *    只在乎最後garbage出現的位置
 *
 *    time  : O(N + N + 1) = O(N)
 *    space : O(1) 
 */
class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        unordered_map<char, int> last;
        int res{};
        for(int i = 0; i < garbage.size(); ++i) { // O(N)
            res += garbage[i].size();
            for(auto& c : garbage[i]) last[c] = i;
        }
        partial_sum(begin(travel), end(travel), begin(travel)); // O(N)
        for(auto& ref : last) { // O(1)
            res += ref.second == 0 ? 0 : travel[ref.second - 1];
        }
        return res;
    }
};
