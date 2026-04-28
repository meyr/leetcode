/* 
 * 這種題目答案都會在其中一個數字
 * 一開始先分析問題
 *
 *    vecs = [2,   4,    6,    8]         --> sum = 20, x = 2
 *if k == 2  2-k + 4-k + 6-k + 8-k = (sum(vecs) - 4*k) / x
 *if k == 4  k-2 + 4-k + 6-k + 8-k = (sum(vecs) - 2*prev_k - 2*k) /x
 *if k == 6  k-2 + k-4 + 6-k + 8-k = (sum(vecs) - 2*prev_k - 0*k) /x
 *if k == 8  k-2 + k-4 + k-6 + 8-k = (sum(vecs) - 2*prev_k + 2*k) /x
 *
 * time  : O(MN + MNlogMN + MN + MN) = O(MNlogMN)
 * space : O(MN)
 */

class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        int m = grid.size(), n = grid[0].size(), sum{}, sz = m * n;
        vector<int> vecs;
        for(auto& row : grid)
            for(auto& n : row) {
                vecs.push_back(n);
                sum += n;
            }
        sort(begin(vecs), end(vecs));
        for(int i = 1; i < m * n; ++i)
            if((vecs[i] - vecs[i - 1]) % x != 0) return -1;
        int ans = INT_MAX;
        for(int i = 0, cnt = sz; i < sz; ++i, cnt -= 2) {
            if((sum - cnt * vecs[i]) % x == 0) {
                ans = min(ans, (sum - cnt * vecs[i]) / x);
            }
            sum -= 2*vecs[i];   // 每次減掉目前的值
        }
        return ans == INT_MAX ? -1 : ans;
    }
};
/*  參考解答
 *
 *  答案只會在排序過nums的中間
 *
 *  time  : O(MN + MNlogMN + MN) = O(MNlogMN)
 *  space : O(MN)
 */
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int>nums;
        int m=grid.size(),n=grid[0].size();
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                nums.push_back(grid[i][j]);
        sort(nums.begin(),nums.end());
        int target=nums[m*n/2],ans=0;
        for(int i=m*n-1;i>=0;i--){
            if(abs(nums[i]-target)%x!=0)
                return -1;
            else
                ans+=abs(nums[i]-target)/x;
        }
        return ans;
    }
};
/*
 *  2026/04/28 daily challenge
 *  參考解答和上面的想法一樣 但是我們排序只是為了找中位數 所以改使用nth_element來降低time complexity
 *
 *  nth_element(start it, mid it, end it) : 只會保證數列在[start it, end it]中, 在mid it之前的都是小於它,
 *                                                                              在mid it之後都是大於等於它
 *  所以可以用來找中位數
 *
 *  time  : O(MN + MN + MN) = O(MN)
 *  space : O(MN)
 */
class Solution {
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        vector<int> nums;
        for(int i = 0; i < grid.size(); ++i) for(int j = 0; j < grid[0].size(); ++j)
            nums.push_back(grid[i][j]);
        int sz = nums.size();
        nth_element(begin(nums), begin(nums) + sz / 2,  end(nums)); // __important__ 使用nth_element取代sort
        int target = nums[sz / 2];
        int ans{};
        for(auto& n : nums) {
            if(abs(n - target) % x != 0) return -1;
            else ans += abs(n - target) / x;
        }
        return ans;
    }
};
