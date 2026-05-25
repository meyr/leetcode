/*  每個node都會產生一個可以訪問的區間 所以我使用range來解 --> TLE
 *  time  : O(N^2)
 */
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        if(s.back() == '1') return false;
        int target = s.size() - 1;
        vector<pair<int, int>> range;
        range.push_back({minJump, maxJump});
        while(!range.empty()) {
            vector<pair<int, int>> tmp;
            for(auto& r : range) {
                for(int i = r.first; i <= min(r.second, target); ++i) {
                    if(i == target) return true;
                    if(s[i] == '0') {
                        int left = i + minJump, right = i + maxJump;
                        if(target >= left && target <= right) return true;
                        if(!tmp.empty() && tmp.back().second >= left)
                            tmp.back().second = right;
                        else tmp.push_back({left, right});
                    }
                }
            }
            range = move(tmp);
        }
        return false;
    }
};
/*  參考解答
 *
 *  每一個node(i) 都是從前面跳過來的 [i - maxJump, i - minJump] 如果這個區間有s[j] == '0' 且 s[j]是可以抵達的 那就可以抵達s[i]
 *
 *  ---- i - 1 - maxJump ------------ i - 1 - minJump ------------ i - 1 ------------------
 *                 /|\ (少了這個點)                    |
 *  那下一個點呢?   |                                  |
 *                  |                                 \|/  (多了這個點)
 *  ------------ i - maxJump ------------------- i - minJump -------------- i ------------------
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int sz = s.size();
        int sum{};
        vector<int> reachable(sz);
        reachable[0] = 1;
        for(int i = 1; i < sz; ++i) {
            if(i - minJump >= 0 && reachable[i - minJump])
                sum++;
            if(i - 1 - maxJump >= 0 && reachable[i - 1 - maxJump])
                sum--;
            if(s[i] == '0' && sum)
                reachable[i] = 1;
        }
        return reachable.back();
    }
};
