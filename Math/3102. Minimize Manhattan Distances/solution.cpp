/*
 *  參考 : https://leetcode.cn/problems/minimize-manhattan-distances/solutions/2829782/zui-xiao-hua-man-ha-dun-ju-chi-by-leetco-dipa/
 *
 *  A(x1, y1), B(x2, y2)
 *  d(A, B) = max(abs(x1 - x2) + abs(y1 - y2))    打開abs會有四種可能
 *          = max(x1 - x2 + y1 - y2,
 *                x1 - x2 + y2 - y1,
 *                x2 - x1 + y1 - y2,
 *                x2 - x1 + y2 - y1);
 *
 *          = max(x1 + y1 - (x2 + y2),
 *                x1 - y1 - (x2 - y2),
 *                x2 - y2 - (x1 - y1),
 *                x2 + y2 - (x1 + y1))
 *
 *          = max(sum(A)  - sum(B),      ---+-->      abs(sum(A) - sum(B))     ---> max(abs(sum(A) - sum(B), abs(diff(A) - diff(B)))
 *                diff(A) - diff(B),   =====|==++=>   abs(diff(A) - diff(B))        
 *                diff(B) - diff(A),   =====|==||
 *                sum(B)  - sum(A));     ---|
 *
 *         
 *  因為使用了multiset 所以 abs(sum(A) - sum(B))   = *sum.rbegin()  - *sum.begin()
 *                          abs(diff(A) - diff(B)) = *diff.rbegin() - *diff.begin()
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) {
        multiset<int> diff, sum;
        for(auto& p : points) {
            diff.insert(p[0] - p[1]);
            sum.insert(p[0] + p[1]);
        }
        int ans{INT_MAX};
        for(auto& p : points) {
            diff.erase(diff.find(p[0] - p[1]));
            sum.erase(sum.find(p[0] + p[1]));
            ans = min(ans, max(*diff.rbegin() - *diff.begin(), *sum.rbegin() - *sum.begin()));
            diff.insert(p[0] - p[1]);
            sum.insert(p[0] + p[1]);
        }
        return ans;
    }
};
