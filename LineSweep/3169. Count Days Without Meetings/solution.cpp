/*  使用line swipe和prefix sum來計算沒有meeting的空檔
 *
 *   [[5,7],[1,3],[9,10]]
 *
 *       1---------4
 *                   5----------8
 *                                9----------11
 * pfs:0 1         0 1          0 1          0
 *
 * [[2,4],[1,3]]
 *
 *       1---------4
 *            2----------5
 *
 * pfs:0 1    2    1     0
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) {
        map<int, int> m;
        for(auto& mt : meetings) {
            m[mt[0]]++;
            m[mt[1] + 1]--;
        }
        int pfs{}, ans{}, prev = 1;
        for(auto& ref : m) {
            if(pfs == 0) ans += ref.first - prev;   // 先判斷之前pfs是否為0
            prev = ref.first;
            pfs += ref.second;
        }
        ans += days - m.rbegin()->first + 1;
        return ans;
    }
};
