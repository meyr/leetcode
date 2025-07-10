/*  因為一個會議可以移動就表示可以在前後找到比它還大的空間
 *  所以使用ava來統計每個會議前後的avaliable time, 並且使用map來統計所有的avaliable time
 *
 *  case1. 除了前後之外 可以找到其他地方塞入此meeting 則 ans = max(ans, prev + nxt + duration)
 *  case2.              找不到可以塞入此meeting 則 ans = max(ans, prev + nxt)
 *
 *  time  : O(N + NlogN) = O(NlogN), N : size of startTime
 *  space : O(N)
 */

class Solution {
public:
    int maxFreeTime(int eventTime, vector<int>& startTime, vector<int>& endTime) {
        int sz = startTime.size();
        vector<int> ava;
        map<int, int> mp;
        ava.push_back(startTime.front());
        mp[ava.back()]++;
        for(int i = 1; i < sz; ++i) {
            ava.push_back(startTime[i] - endTime[i - 1]);
            mp[ava.back()]++;
        }
        ava.push_back(eventTime - endTime.back());
        mp[ava.back()]++;
        int ans{};
        for(int i = 0; i < sz; ++i) {
            int prev = ava[i];
            int nxt = ava[i + 1];
            int duration = endTime[i] - startTime[i];
            mp[prev]--;                                     // 去掉前後空格之後
            mp[nxt]--;
            auto it = mp.lower_bound(duration);             // 找出還可以塞入此meeting的空格
            while(it != mp.end() && it->second == 0) it++;
            if(it != mp.end())                              // 有找到
                ans = max(ans, prev + nxt + duration);
            else                                            // 沒找到
                ans = max(ans, prev + nxt);
            mp[prev]++;
            mp[nxt]++;
        }
        return ans;
    }
};
/* improve : 可以紀錄left, right最大空間 或是只記錄前三大空間, 因為prev, nxt就佔了兩個
 * 這樣改進就可以達到time: O(N)
 */
