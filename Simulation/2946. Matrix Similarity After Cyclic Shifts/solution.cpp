/*
 * 一開始照著題意 把vector shift 因為是easy所以可以過 但是TC不是很好
 *
 * Time  : O(M(N+N+N+N)) = O(4MN) = O(MN)
 * space : O(N)
 */
class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        k %= mat[0].size();
        for(int y = 0; y < mat.size(); ++y) {
            int s = (y % 2) ? mat[0].size() - k : k;
            vector<int> tmp(mat[y]);
            reverse(begin(tmp), begin(tmp) + s);
            reverse(begin(tmp) + s, end(tmp));
            reverse(begin(tmp), end(tmp));
            if(tmp != mat[y]) return false;
        }
        return true;
    }
};
/*
 * 參考解答 因為是shift直接比較就可以
 *
 * time  : O(MN)
 * space : O(1)
 */
class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) {
        int m = mat.size(), n = mat[0].size();
        k %= n;
        for(int y = 0; y < m; ++y) {
            int s = y % 2 ? -k : k;
            for(int x = 0; x < n; ++x) {
                if(mat[y][x] != mat[y][(x + s + n) % n])
                    return false;
            }
        }
        return true;
    }
};
