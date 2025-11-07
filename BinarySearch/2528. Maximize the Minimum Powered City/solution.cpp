/*  參考解答: https://leetcode.com/problems/maximize-the-minimum-powered-city/solutions/7326257/maximize-the-minimum-powered-city-by-lee-y3gm/
 *
 *  Greedy point: 如果電力不足要增加power station, 對目前i來說加在哪裡比較好?
 *                
 *                因為我們都是從左至右檢查, 如果發現不足, 表示左邊已經符合了, 所以只要處理目前的node.
 *                處理目前的node最貪婪的做法就是把power station加在i + r的地方, 這樣受益的node最多
 *
 *  這邊還使用了line sweep概念, 方便計算因為增加power station必須計算目前的power方法
 *  
 *  使用binary search原因, 新增k個power station可以達到min power 為 val, 則val - 1, val - 2... 也都可以達到
 *
 *  min power : 1, 2, 3, 4, 5, 6, 7    k = 2
 *  check()     o  o  o  o  x  x  x
 *
 *  time  : O(N + N + N + NlogM) = O(NlogM)
 *  space : O(N)
 */
class Solution {
public:
    long long maxPower(vector<int>& stations, int r, int k) {
        int n = stations.size();
        vector<long long> cnt(n + 1);
        long long left{LLONG_MAX}, right{k + 1};    // left : 目前的最小值, right : 全部power station + k + 1
        for (int i = 0; i < n; i++) {        // line sweep概念 只記錄左右兩邊的邊界
            int st = max(0, i - r);          // O(N)
            int ed = min(n, i + r + 1);      // __important__ 這邊是上邊界的下一個
            cnt[st] += stations[i];
            cnt[ed] -= stations[i];
            left = min(left, (long long)stations[i]);
            right += stations[i];
        }

        auto check = [&](long long target) -> bool {
            vector<long long> diff(cnt);// 複製一份 cnt
            long long sum = 0;          // 目前的power
            long long remaining = k;    // 剩下可以新增的power station數量
                                                                           
            for (int i = 0; i < n; i++) // O(N)                           {
                sum += diff[i];                         // 計算目前的power
                if (sum < target) {                     // 如果目前的power預期target還少
                    long long add = target - sum;       // 需要增加的power station數量
                    if (remaining < add) return false;  // 剩下的不夠增加
                    diff[min(n, i + 2 * r + 1)] -= add; // __importatn__ 設置在 i + r, 影響的範圍是[i, i + 2*r], 所以必須在i + 2*r + 1扣掉
                    remaining -= add;
                    sum += add;                         // 設置了新power station所以目前的power必須更新
                }
            }
            return true;
        };

        while (left < right) {                          // O(NlogM), M : hi - lo, 每次check都要走訪N
            long long mid = left + (right - left) / 2;
            if (check(mid)) left = mid + 1;
            else right = mid;
        }
        return left - 1;
    }
};
