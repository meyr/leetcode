/*
 *   標準binary search 題目
 *   注意 最後一個dist不用等整數時間
 *
 *   speed : 1, 2, 3, [4], 5, 6  hour = 4
 *           x  x  x   o   o  o
 */
class Solution {
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        if(ceil(hour) < dist.size()) return -1;
        else if(hour == dist.size()) return *max_element(begin(dist), end(dist));
        else {
            int left = 1, right = INT_MAX;
            while(left < right) {
                int mid = left + (right - left) / 2;
                double take{};
                for(int i = 0; i < dist.size() - 1; ++i)
                    take += (dist[i] + mid - 1) / mid;
                take += (double)dist.back() / mid;
                if(take <= hour) right = mid;
                else left = mid + 1;
            }
            return left;
        }
    }
};


