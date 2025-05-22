/* 對bookings排序之後使用prefix sum
 *
 * time  : O(NlogN + N) = O(NlogN)
 * space : O(logN + N + N) = O(N)
 */
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        sort(begin(bookings), end(bookings));
        vector<int> rtn(n);
        vector<int> m(n + 2);
        for(int i = 1, j = 0, cur = 0; i <= n; ++i) {
            cur += m[i];
            while(j < bookings.size() && i == bookings[j][0]) {
                cur += bookings[j][2];
                m[bookings[j][1] + 1] -= bookings[j][2];
                j++;
            }
            rtn[i - 1] = cur;
        }
        return rtn;
    }
};
