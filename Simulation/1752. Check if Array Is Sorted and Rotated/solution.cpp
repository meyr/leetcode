/*
    我的解法是: 先找出轉折點p 然後前後檢查

*/
class Solution {
public:
    bool check(vector<int>& nums) {
        int p{};
        for(int i = 1; i < nums.size(); ++i) {
            if(nums[i] < nums[i - 1]) {
                if(p) return false;
                else p = i;
            }
        }
        if(!p) return true;
        return is_sorted(begin(nums), begin(nums) + p) &&
               is_sorted(begin(nums) + p, end(nums)) &&
               nums.front() >= nums.back();
    }
};
/*
    其實後面的is_sorted是多餘的因為前面的for loop已經檢查過了
*/
class Solution {
public:
    bool check(vector<int>& nums) {
        int p{};
        for(int i = 1; i < nums.size(); ++i) {
            if(nums[i] < nums[i - 1]) {
                if(p) return false;
                else p = i;
            }
        }
        if(!p) return true;
        return nums.front() >= nums.back();
    }
};
/*
    參考:https://leetcode.com/problems/check-if-array-is-sorted-and-rotated/solutions/1053508/javacpython-easy-and-concise-by-lee215-15tm/
    想法和上面一樣只是檢查最後 nums.front() >= nums.back()也被放在for loop中
    不過這樣反而會增加執行時間 因為每次都要mod A.size() 何不最後再檢查?
*/
class Solution {
public:
    bool check(vector<int>& A) {
        for (int i = 0, k = 0; i < A.size(); ++i)
            if (A[i] > A[(i + 1) % A.size()] && ++k > 1)
                return false;
        return true;
    }
};
