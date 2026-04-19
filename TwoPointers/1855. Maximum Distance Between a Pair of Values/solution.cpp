/*  既然是non-increasing 數列 感覺就是可以用two pointer來處理
 *  
 *  最大值會出現在哪裡? 因為distance定義是j - i 所以最大值會出現在j = nums2.size() - 1, i = 0
 *  所以j從後面開始找, i也從後面開始只要符合nums1[i]<= nums2[j]就計算distance 
 *  但是使用max(0, j - i) 避免負數
 *
 *  如果條件不符合 nums1[i] <= nums2[j] 就把i往前移動
 *  time  : O(N+M)  因為兩個ponter只會走訪nums1, nums2一次
 *  space : O(1)
 */
class Solution {
public:
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int ans{}, i = nums1.size() - 1;
        for(int j = nums2.size() - 1; j >= 0; --j) {
            while(i >= 0 && nums1[i] <= nums2[j]) {
                ans = max(ans, max(0, j - i));
                i--;
            }
            if(i < 0) break;
        }
        return ans;
    }
};
