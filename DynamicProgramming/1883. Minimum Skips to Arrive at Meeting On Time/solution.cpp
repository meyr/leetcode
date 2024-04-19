/*
 * 參考解答 : https://leetcode.com/problems/minimum-skips-to-arrive-at-meeting-on-time/solutions/1242066/2d-dp/
 *
 * speed * housrs 總共可以走的距離
 */
class Solution {
    vector<vector<int>> mem;
    int dfs(vector<int>& dist, int i, int skips, int speed) {
        // i < 0 全部走完
        // skip < 0 沒有 skip可以用了
        if(skips < 0 || i < 0) return skips < 0 ? 1e9 : 0;
        if(~mem[i][skips]) return mem[i][skips];
        return mem[i][skips] = min(
            // skip，不需要走額外的距離
            dist[i] + dfs(dist, i - 1, skips - 1, speed), 
            // 不skip，因為要等待到整數，所以加上以前的距離(因為可能有非整數的部分)
            (dfs(dist, i - 1, skips, speed) + dist[i] + speed - 1) / speed * speed);
    }
public:
    int minSkips(vector<int>& dist, int speed, int hours) {
        if((long long)speed * hours > 1e9) return 0;
        if(accumulate(begin(dist), end(dist), 0) > speed * hours) return -1;
        mem.resize(dist.size(), vector<int>(dist.size(), -1));
        for(int skips = 0; skips < dist.size(); ++skips) {
            // 走到dist.size() - 2的距離 小於等於 總共可以走的距離 - dist.back() => 可以到達
            if(dfs(dist, dist.size() - 2, skips, speed) <= hours * speed - dist.back())
                return skips;
        }
        return -1;
    }
};
