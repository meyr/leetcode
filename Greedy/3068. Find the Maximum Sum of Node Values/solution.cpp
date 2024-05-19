/*
 *  參考解答
 *  https://leetcode.com/problems/find-the-maximum-sum-of-node-values/solutions/4811460/greedy-sacrifice/
 *
 *  這邊的重點是xor 也就是說不管你怎麼選一定會有__偶數__個node被你改變
 *  而且是任意偶數個node，所以我們先找出n^k > n 的node
 *  如果 這樣的node為__基數__那就是犧牲最小的那一個 min(s, abs(n - (n^k)))
 *
 */
class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        long long sum{}, cnt{}, sacrifice = INT_MAX;
        for(long long n : nums) {
            sum += max(n ^ k, n);
            cnt += (n ^ k) > n;
            sacrifice = min(sacrifice, abs(n - (n ^ k)));
        }
        return sum - (cnt % 2 ? sacrifice : 0);
    }
};
