/*
 *  因為一次可以取2或3個task 且要找出最小round 所以竟可能先取3 tasks
 *
 */
class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        unordered_map<int, int> m; // value, count
        for(auto& t : tasks) m[t]++;
        int ans{};
        for(auto& ref : m) {
            if(ref.second == 1) return -1;
            if(ref.second % 3 == 0) ans += ref.second / 3;
            else if(ref.second % 3 == 2) ans += ref.second / 3 + 1; // 先取一個2 tasks
            else ans += 2 + (ref.second - 4) / 3; // 先取兩個2 tasks
        }
        return ans;
    }
};
/*
    2 --> 1
    3 --> 1
    4 --> 2 + 2
    7 --> 2 + 2 + 3
    10 --> 2 + 2 + 3 + 3
*/
