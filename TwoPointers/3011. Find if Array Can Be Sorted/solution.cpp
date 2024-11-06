/* 先找出set bit一樣的範圍然後對它進行排序
 * 最後判斷結果是否為sorted array
 * 
 * time  : O(NlogN + N) = O(NlogN)
 * space : O(logN)
 */
class Solution {
public:
    bool canSortArray(vector<int>& nums) {
        int i = 0;
        while(i < nums.size()) {
            int j = i + 1;
            while(j < nums.size() && __builtin_popcount(nums[i]) == __builtin_popcount(nums[j]))
                j++;
            sort(begin(nums) + i, begin(nums) + j);
            i = j;
        }
        return is_sorted(begin(nums), end(nums));
    }
};
/*  不要需最後在判斷是否為sorted array
 *  只要在每次排序完判斷前後關係即可 nums[i - 1] < nums[i]
 *
 *  time  : O(NlogN)
 *  space : O(logN)
 */
class Solution {
public:
    bool canSortArray(vector<int>& nums) {
        int i = 0;
        while(i < nums.size()) {
            int j = i + 1;
            while(j < nums.size() && __builtin_popcount(nums[i]) == __builtin_popcount(nums[j]))
                j++;
            sort(begin(nums) + i, begin(nums) + j);
            if(i > 0) {
                if(nums[i] < nums[i - 1]) return false;
            }
            i = j;
        }
        return true;
    }
};
/* 不需要sort因為只在乎最大最小值
 * 所以修改上面的code只記錄maxv和minv
 * 
 * time  : O(N)
 * space : O(1)
 */
class Solution {
public:
    bool canSortArray(vector<int>& nums) {
        int i = 0;
        while(i < nums.size()) {
            int j = i + 1;
            int maxv = nums[i], minv = nums[i];
            while(j < nums.size() && __builtin_popcount(nums[i]) == __builtin_popcount(nums[j])) {
                minv = min(minv, nums[j]);
                maxv = max(maxv, nums[j]);
                j++;
            }
            nums[i] = minv;
            nums[j - 1] = maxv;
            if(i > 0 && nums[i] < nums[i - 1]) return false;
            i = j;
        }
        return true;
    }
};
