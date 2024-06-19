/*
 *  day 1, 2, 3, 4, 5, 6, 7 
 *  b   0, 0, 1, 1, 2, 2, 3
 *                  *             
 *
 *  標準的binary search 題目
 *
 *  time  : O(NlogM), M:right - left + 1, N : length of bloomDay
 *  space : O(1)
 *
 *  或是可以先使用 auto [minv, maxv] = minmax_element(begin(bloomDay), end(bloomDay)); 先找出最大最小值
 *  然後 int left = *minv, right = *maxv; 
 *  但是時間會多個O(N)
 */
class Solution {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if((long)m * k > bloomDay.size()) return -1;
        int left = 1, right = 1e9;
        while(left < right) {
            int mid = left + (right - left) / 2;
            int bouquet{}, cnt{};
            for(auto& b : bloomDay) {
                if(b <= mid) cnt++;
                else cnt = 0;
                if(cnt == k) {
                    bouquet++;
                    cnt = 0;
                }
            }
            if(bouquet >= m) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
