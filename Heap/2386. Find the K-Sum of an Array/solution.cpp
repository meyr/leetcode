/*
     參考解答 : https://leetcode.com/problems/find-the-k-sum-of-an-array/solutions/2465961/decreasing-subsequence-sums/
                這邊有證明 sum - nums[i+1] 和 sum - nums[i+1] + nums[i] 可以列舉所有subsequence的組合

     參考test.cpp　確實使用上述可以列舉所以subsequence sum
*/

class Solution {
public:
    long long kSum(vector<int>& nums, int k) {
        long long res{};
        for(auto& n : nums) {
            if(n > 0) res += n;
            else n *= -1;
        }
        if(k == 1) return res; // 最大subsequence sum
        priority_queue<pair<long long, int>> pq; //maxheap
        sort(begin(nums), end(nums));
        pq.push(make_pair(res - nums[0], 0)); // 第二大
        while(--k) {
            auto [s, i] = pq.top(); pq.pop();
            if(i + 1 < nums.size()) {// 還有下一個
                pq.push(make_pair(s - nums[i + 1], i + 1));
                pq.push(make_pair(s - nums[i + 1] + nums[i], i + 1));
            }
            res = s;
        }
        return res;
    }
};
/*
    [1, 2, 3, 4, 5] k = 1
    [5, 4, 3, 2]    k = 2, priority_queue initial state
         |
         |            k = 3
    [5, 4, 3] or [5, 4, 3, 1]
       k = 4/5          |
                        |        k = 4/5
                 [5, 4, 1] or [5, 4, 2, 1]       
*/
