/*
 *  從下面的推論得知 所有的paid group的費用 = max_rate * total quality
 *  其中rate = wage / quality
 *
 *  1. 將rate從小到大排序, 則最大rate永遠是最後一個
 *  2. 因為為了得到最小的費用 所以每次都丟掉最大的quality --> 使用max heap
 *
 *  time  : O(N + NlogN + NlogK) = O(NlogN)
 *  space : O(N + logN + K) = O(N)
 */
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) {
        vector<pair<double, int>> rate;
        int sz = quality.size();
        for(int i = 0; i < sz; ++i) // O(N)
            rate.push_back({1.0 * wage[i] / quality[i], i}); // rate, index
        sort(begin(rate), end(rate)); //O(NlogN)
        priority_queue<int> pq;// quality
        int sumOfQuality{};
        // 兩個for loop全部跑完所有element 所以O(NlogK)
        for(int i = 0; i < k; ++i) {
            sumOfQuality += quality[rate[i].second];
            pq.push(quality[rate[i].second]);
        }
        double ans = rate[k - 1].first * sumOfQuality;
        for(int i = k; i < sz; ++i) {
            sumOfQuality += quality[rate[i].second] - pq.top();
            pq.pop();
            pq.push(quality[rate[i].second]);
            ans = min(ans, rate[i].first * sumOfQuality);
        }
        return ans;
    }
};
/*
    [10, 20, 5] [70, 50, 30], k = 2

    case 1 : [10, 20][70, 50] -> 70 + 140 = 210
              7   2.5 ->max(7, 2.5) * (10 + 20) = 210
    case 2 : [10, 5] [70, 30] -> 70 + 35  = 105 (minimal)
              7   6 wage/quality -> max(7, 6) * 15 = 105
    case 3 : [20, 5] [50, 30] -> 120 + 30 = 150
              2.5 6 -> max(2.5, 6) * 25 = 150
*/

