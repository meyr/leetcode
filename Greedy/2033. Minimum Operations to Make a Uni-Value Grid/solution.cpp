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
