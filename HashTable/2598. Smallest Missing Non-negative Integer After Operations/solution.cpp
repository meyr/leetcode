/*  因為可以對nums[i]進行任意次數的+/- value所以把nums[i] 取 nums[i] % value
 *  所有的數都可以從nums[i]%value來拚出來
 *  
 *  time  : O(N + N) = O(N)
 *  space : O(N)
 */
class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        unordered_map<int, int> um;
        for(const auto& n : nums)
            um[((n % value) + value) % value]++; // 避免有負數的情況
        for(int i = 0; ; ++i) {
            if(--um[i % value] < 0)
                return i;
        }
        return -1;
    }
};
