/*
 *  目標是從num1排成num2且 priority 都是一樣
 *
 *  先看看 兩個極性相減 的結果    o - o = e     3 - 1 = 2
 *                                o - e = o     3 - 2 = 1
 *                                e - o = o     4 - 1 = 3
 *                                e - e = e     4 - 2 = 2
 *  因為nums2[i] = nums1[i] 也就是希望的極性一樣 就直接取
 *      nums2[i] = nums1[i] - nums1[j], i != j, nums1[i] - nums1[j] >= 1 因為是 distinct integer所以只要取比自己小的一定會符合
 *
 *      重點是最小的數字 因為沒有比自己還小的數字 所以用min(nums1) 來當最終的極性
 *      如果min(nums1)是odd, 之後遇到odd就是取   遇到even就是拿它減掉min(nums1) 也是odd 所以直接return true
 *      如果min(nums1)是even, 之後遇到even就是取 遇到odd就是看之前有沒有odd 因為odd - odd = even
 *                                               但是第一個odd一定不會遇到odd所以是false
 *
 *  time  : O(NlogN)
 *  space : O(logN)
 */
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        sort(begin(nums1), end(nums1));
        if(nums1.front() % 2) return true;  // first is odd
        else {  // first is even
            for(int i = 1, ocnt = 0; i < nums1.size(); ++i) {
                if(nums1[i] % 2 && !ocnt) return false;
                ocnt += nums1[i] % 2;
            }
            return true;
        }
    }
};
/*
 *  根據上面的結論 只要統計minval和oddcnt即可判斷
 *
 *  time  : O(N)
 *  sapce : O(1)
 */
class Solution {
public:
    bool uniformArray(vector<int>& nums1) {
        int minval{INT_MAX}, oddcnt{};
        for(auto& n : nums1) {
            minval = min(minval, n);
            oddcnt += n % 2;
        }
        if(minval % 2) return true;
        else return oddcnt == 0;
    }
};
