/*
 *  參考 : https://leetcode.cn/problems/find-the-number-of-good-pairs-ii/solutions/2928182/you-zhi-shu-dui-de-zong-shu-ii-by-leetco-obro/
 *
 *  因為 nums1[i] 可以被 nums2[j] * k 整除 意味著 nums1中可以被 nums2[j] * k, nums2[j] * k * 2, nums2[j] * k * 3, ... 整除都算是nums2[j] * k的答案
 *   
 */
class Solution {
public:
    long long numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        unordered_map<int, long long> count1, count2;
        int max1{};
        for(auto& n : nums1) {
            count1[n]++;
            max1 = max(max1, n);
        }
        for(auto& n : nums2) count2[n]++;
        long long ans{};
        for(auto& ref : count2) {
            int a = ref.first, cnt = ref.second;
            for(int b = a * k; b <= max1; b += a * k) {
                if(count1.count(b)) ans += count1[b] * cnt;
            }
        }
        return ans;
    }
};
