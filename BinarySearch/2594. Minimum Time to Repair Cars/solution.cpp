/*
    minutes : 1, 2, 3,  4, 5, 6
    cars      0, 1, 1, [2], 2, 3
                    <  >=

    time  : O(NlogM), N : size of ranks, M : right - left
    space : O(1)
*/
class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        long long left = 1, right = 1e14;
        while(left < right) {
            long long mid = left + (right - left) / 2;
            long long cnt{};
            for(auto& r : ranks) 
                cnt += (int)sqrt(mid / r);
            if(cnt >= cars) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};

