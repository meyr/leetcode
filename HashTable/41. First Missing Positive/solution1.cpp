/*
 *    比較直覺的想法是先排序
 *    然後找出缺的positive integer
 *
 *    time complexity  : O(NlogN) 不符合題目要求
 */

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        sort(begin(nums), end(nums)); // O(NlogN)
        auto it = lower_bound(begin(nums), end(nums), 1);
        if(it == nums.end() || *it != 1) return 1;
        else {
            int j = 1;
            for(; it != nums.end(); ++it, ++j) { // O(N)
                while(next(it) != nums.end() && *it == *next(it)) it++;
                if(*it != j) return j;
            }
            return j;
        }
    }
};
