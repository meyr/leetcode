/*  參考: https://leetcode.com/problems/maximum-manhattan-distance-after-k-changes/solutions/6360121/revert-first-k-occurrence-of-n-e-or-n-w-4flda/
 *
 *  因為有四個象限 所以每個象限都走看看 看哪一個象限可以到達最遠
 *
 *  time  : O(4N) = O(N)
 *  space : O(1)
 */
class Solution {
public:
    int maxDistance(string s, int k) {
        int ans = 0;
        char dir[4][2] = {{'N', 'E'}, {'N', 'W'},{'S', 'E'},{'S', 'W'}}; // 希望遇到的char
        //                 第一象限   第二象限    第四象限    第三象限
        for(auto d: dir) {
            for(int i = 0, curr = 0, t = k; i < s.size(); ++i){
                if(s[i] == d[0] || s[i] == d[1])
                    curr++;
                else {                              // 不是期待的方向 使用k來換一個想要的方向
                    if(t > 0 ) { t--; curr++; }
                    else curr--;
                }
                ans = max(ans, curr);
            }
        }
        return ans;
    }
};
