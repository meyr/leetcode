/*  一開始就覺得這是個greedy題目 因為cost = min(num1, num2)
 *  所以每次交換都要和最小的
 *  寫出了以下的解答，但是有錯
 */
class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        unordered_map<int, int> um, b1;
        for(auto& f : basket1) {
            um[f]++;
            b1[f]++;
        }
        for(auto& f : basket2)
            um[f]++;
        vector<int> nums;
        for(auto& ref : um) {
            if(ref.second % 2) return -1;
            int cnt = abs(b1[ref.first] - ref.second / 2);
            for(int i = 0; i < cnt; ++i)
                nums.push_back(ref.first);
        }
        sort(begin(nums), end(nums));
        int sz = nums.size();
        return accumulate(begin(nums), begin(nums) + sz / 2, 0LL);
    }
};
/*  ref : https://leetcode.com/problems/rearranging-fruits/solutions/3143917/javacpython-two-ways-to-swap-by-lee215-5p2w/
 *  
 *  上面錯在少考慮了一個交換情況。   我要把 200和999交換，可以先和1交換，
 *  basket1 = [100, 100, 200, 200]
 *  basket2 = [1, 1, 999, 999]
 *
 *  basket1 = [100, 100, 200, 1*]    再用1和999交換
 *  basket2 = [1, 200*, 999, 999]
 * 
 *  basket1 = [1000, 1000, 200, 999*] 這樣也可以達到200和999交換，但是cost只有1 * 2
 *  basket2 = [1, 200*, 999, 1*]
 *
 *  所以每次要交換的時候，檢查正常交換或是使用兩次最小值交換，那個比較划算。
 *
 *  time  : O(N + N + N + N/2) = O(N)
 *  space : O(N + N) = O(N)
 */
 class Solution {
public:
    long long minCost(vector<int>& basket1, vector<int>& basket2) {
        map<int, int> um;
        for(auto& f : basket1) um[f]++;
        for(auto& f : basket2) um[f]--;
        long long res{};
        vector<int> swaps;
        int small = um.begin()->first;
        for(auto& [f, c] : um) {
            if(c % 2) return -1;
            for(int i = 0; i < abs(c) / 2; ++i)
                swaps.push_back(f);
        }
        for(int i = 0; i < swaps.size() / 2; ++i)
            res += min(swaps[i], small * 2);
        return res;
    }
};
