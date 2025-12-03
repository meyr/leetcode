/*  很直覺的使用以下code結果TLE
 *  nums.size()  <= 5*10^4  -->必須要O(NlogN)以下
 *
 *  time  : O(N(N + logN + logN) = O(N^2)
 *  sapce : O(N) 
 */
class Solution {
public:
    int reversePairs(vector<int>& nums) {
        multiset<long long> ms;
        int ans{};
        for(auto& n : nums) { 
            auto it = upper_bound(begin(ms), end(ms), (long long)n * 2);
            ans += distance(it, ms.end());
            ms.insert(n);
        }
        return ans;
    }
};
/*  參考AI解答: 這邊使用divide and conqure
 *
 *  why divide and conqure?
 *  從題目來看 如果一個vector是排序過的  [a, b, c, d] 其中a < b < c < d 則我們可以輕鬆找出reverse pair
 *  因為可以使用兩個pointer i, j  [a, b, c, d] , 找出nums[i] > 2 * nums[j] -->O(N)
 *                                 i     j
 *  int ans{};
 *  for(int i = 0; i <= mid && j < nums.size(); ++i) {
 *      while(j < nums.size() && nums[j] <= 2 * nums[i]) ++j;
 *      ans += nums.size() - j;
 *  }
 *  
 *  處理完subarray1, 和 subarray2之後 再將兩個subarray進行排序
 *
 *  time  : O(NlogN)
 *  space : O(logN)
 */
class Solution {
private:
    using ll = long long;
    int mergeAndCount(std::vector<int>& nums, int left, int mid, int right) {
        ll count = 0;
        for (int i = left, j = mid + 1; i <= mid; ++i) {
            while (j <= right && (ll)nums[i] > 2 * (ll)nums[j]) j++; // 找出nums[i] <= nums[j] * 2 則j以下都是reverse pair
            count += j - (mid + 1);
        }
        vector<int> tmp(right - left + 1);  // 將nums[left, mid] 和nums[mid + 1, right] 排序
        int i = left, j = mid + 1, k = 0;
        while(i <= mid && j <= right) {
            if(nums[i] <= nums[j]) tmp[k++] = nums[i++];
            else tmp[k++] = nums[j++];
        }
        while(i <= mid) tmp[k++] = nums[i++];
        while(j <= right) tmp[k++] = nums[j++];
        for(int i = 0; i < tmp.size(); ++i)
            nums[left + i] = tmp[i];
        return count;
    }
    int mergeSort(std::vector<int>& nums, int start, int end) { // merge sort : 先對前後subarray排序 再一起排序
        if (start >= end) return 0;
        int mid = start + (end - start) / 2;
        int count = mergeSort(nums, start, mid);
        count += mergeSort(nums, mid + 1, end);
        count += mergeAndCount(nums, start, mid, end);
        return count;
    }
public:
    int reversePairs(std::vector<int>& nums) {
        return mergeSort(nums, 0, nums.size() - 1);
    }
};
