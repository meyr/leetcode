/*
    maxcandies = 1, 2, 3, 4, 5,  6,  7, 8
    count      = 9, 8, 8, 7, 7, [7], 6, 6    if k = 7
                                >=   <
*/

class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        long long total = accumulate(begin(candies), end(candies), 0LL);
	// special case
        if(total < k) return 0;
        else if(total == k) return 1;
        
	long left = 1, right = total / k + 1;
        while(left < right) {
            long mid = left + (right - left) / 2;
            long cnt{};
            for(auto& c : candies) cnt += c / mid;
            if(cnt < k) right = mid;
            else left = mid + 1;
        }
        return left - 1;
	// time  : O(NlogT) : N length of candies, T = total / K
	// space : O(1) 
    }
};
/*  2025/03/14 daily challenge
 *  想法和以前類似 看到題目就想到是binary search
 *
 */
class Solution {
public:
    int maximumCandies(vector<int>& candies, long long k) {
        long long sum = accumulate(begin(candies), end(candies), 0L);
        if(k > sum) return 0;
        else if(k == sum) return 1;
        else {
            int left = 1, right = *max_element(begin(candies), end(candies)) + 1;   // 參考以前的解答 right = sum / k + 1會比較好
            while(left < right) {
                int mid = left + (right - left) / 2;
                long long cnt{};
                for(auto& c : candies)
                    cnt += c / mid;
                if(cnt < k) right = mid;
                else left = mid + 1;
            }
            return left - 1;
        }
    }
};
/*
    mid : 1, 2, 3,  4,  5, 6
    cnt : 8, 7, 6, [6], 5, 5
                    >=  <
*/
