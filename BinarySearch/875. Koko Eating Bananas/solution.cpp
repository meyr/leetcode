/*
    k = 1, 2,  3, 4, 5
    h = 10,9, [8], 8, 7
            >  <=
*/
class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = 1e9;
        while(left < right) {
            int mid = left + (right - left) / 2;
            int take{};
            for(auto& p : piles)
                take += (p + (mid - 1)) / mid;
            if(take <= h) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
