/*  因為是bitwise AND找出最大值的subarray length
 *  所以一定會發生在包括最大值的subarray
 *  先找出最大值 然後向左向右尋找符合的subarray
 *
 *  這邊想錯一個點 : (mval & nums[left]) == mval 是不必要的因為任何小於mval的值都會使bitwise AND變小
 *  所以只要找跟mval一樣的即可
 */
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int left{}, right{}, ans{};
        int mpos{-1}, mval{};
        while(right < nums.size()) {
            //cout << right << endl;
            mpos = max_element(begin(nums) + right, end(nums)) - begin(nums);
            if(nums[mpos] >= mval) {
                mval = nums[mpos];
                left = mpos, right = mpos;
                while(left >= 0) {
                    if((mval & nums[left]) == mval) left--;
                    else break;
                }
                while(right < nums.size()) {
                    if((mval & nums[right]) == mval) right++;
                    else break;
                }
                ans = max(ans, right - left - 1);
            } else break;
        }
        return ans;
    }
};
/*
 *  以下是修正的程式
 */
class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int mval = *max_element(begin(nums), end(nums));
        int ans{}, len{};
        for(auto& n : nums) {
            len = n == mval ? len + 1 : 0;
            ans = max(ans, len);
        }
        return ans;
    }
};
