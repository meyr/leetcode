/*  
 *  一開始的想法式 遇到rains[i] == 0 的時候當然是先抽乾 接下來index最小且full的lake
 *  所以使用unordered_map<int, queue<int>> um 收集每個lake的index
 *
 *  當一個lake full的時候 就把接下來的index 往minheap塞
 *  當遇到rains[i] == 0 的時候 就從minheap拿出一個最小的index
 *
 */
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int sz = rains.size();
        unordered_map<int, queue<int>> um; // no of lake, day
        for(int i = 0; i < sz; ++i)
            if(rains[i] != 0)
                um[rains[i]].push(i);
        vector<int> ans(sz, -1);
        unordered_set<int> full;
        priority_queue<int, vector<int>, greater<>> pq;

        for(int i = 0; i < sz; ++i) {
            int lake = rains[i];
            if(lake != 0) {
                if(full.count(lake)) return {}; // 已經滿了 會早成flood
                full.insert(lake);
                while(!um[lake].empty() && um[lake].front() <= i) um[lake].pop(); // 跳過已經使用過的index
                if(!um[lake].empty()) {                                           // 如果還有推入一個index
                    pq.push(um[lake].front());
                    um[lake].pop();
                }
            } else {
                if(!pq.empty()) {
                    int idx = pq.top(); pq.pop();
                    ans[i] = rains[idx];
                    full.erase(ans[i]);
                } else {                                // 沒有任何full lake就隨便選一個
                    for(int j = 1; j < sz; ++j)
                        if(!full.count(j)) {
                            ans[i] = j;
                            break;
                        }
                }
            }
        }
        return ans;
    }
};
/*
 *   另一種解法是使用binary search
 *
 */
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int sz = rains.size();
        vector<int> rtn(sz, -1);
        unordered_map<int, int> m; // lake, index
        set<int> zero; // index of zero
        for(int i = 0; i < sz; ++i) {
            if(rains[i] == 0) {
                zero.insert(i);
                rtn[i] = 1;         // ??
            } else {
                if(m.count(rains[i])) { // 此lake已經滿了
                    int lastIndex = m[rains[i]]; // 上次灌滿的index
                    auto zeroIndex = zero.upper_bound(lastIndex); // 從zero中找出比lastIndex還大的值 用這個zero把它抽掉
                    // 沒有zero可以抽掉lake的水
                    if(zeroIndex == zero.end()) return {}; 
                    rtn[*zeroIndex] = rains[i];
                    zero.erase(zeroIndex);
                }
                m[rains[i]] = i;
            }
        }
        return rtn;
    }
};
