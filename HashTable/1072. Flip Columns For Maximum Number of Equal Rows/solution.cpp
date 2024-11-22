/*  參考解答 : https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/solutions/303847/simple-c-solution-with-comments/
 *
 *  重點不是每個column如何flip而是每個row和第一個element的相關程度
 *                            
 *   0, 0, 0  --> 0, 0, 0    其中0表示相同, 1表示不同
 *   0, 0, 1  --> 0, 0, 1
 *   1, 1, 0  --> 0, 0, 1
 */
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<string, int> m;
        int ans{};
        for(int y = 0; y < matrix.size(); ++y) {
            string str{"0"}; // 因為最長長度為300 所以使用string來表示
            for(int i = 1; i < matrix[y].size(); ++i)
                str += matrix[y][i] == matrix[y][0] ? '0' : '1';
            m[str]++;
            ans = max(ans, m[str]);
        }
        return ans;
    }
};
/* 相同解法 可以使用bitset來加速
 *
 */
class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        unordered_map<bitset<300>, int> m;
        int ans{};
        for(int y = 0; y < matrix.size(); ++y) {
            bitset<300> bs{};
            for(int i = 1; i < matrix[y].size(); ++i)
                if(matrix[y][0] != matrix[y][i])
                    bs[i].flip();
            ans = max(ans, ++m[bs]);
        }
        return ans;
    }
};
