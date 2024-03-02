/*   參考lee215的解答
 *
 *   也算是一種brute force解答，
 *   只是用了prefix sum，把O(N^4) 變成O(N^3)
 *   檢查Constraints，長度為100剛好可以使用O(N^3)
 *
 */

class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        for(auto& mat : matrix)
            partial_sum(begin(mat), end(mat), begin(mat));
        unordered_map<int, int> counter;
        int ans{};
        for(int left = 0; left < n; ++left) {
            for(int right = left; right < n; ++right) {
                counter = {{0, 1}}; // 清掉，只留下一個。因為每一次都是重新開始統計
                int cur = 0;
                for(int y = 0; y < m; ++y) {
                    //加上 matrix[y][left - 1] ~ matrix[y][right]
                    cur += matrix[y][right] - (left > 0 ? matrix[y][left - 1] : 0);
                    ans += counter[cur - target];
                    counter[cur]++;
                }
            }
        }
        return ans;
    }
};
