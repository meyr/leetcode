/*
 *  每個cur開頭的row可以有多少選擇? 1本, 2本, 3本 只要滿足thinkness <= shelfWidth
 *  
 *  time  : O(N^2)
 *  space : O(N)
 */
class Solution {
    int helper(vector<vector<int>>& books, int width, int cur) {
        if(~mem[cur]) return mem[cur];
        int rtn{INT_MAX}, w{}, h{};
        for(int i = cur; i < books.size() && w <= width; ++i) {
            w += books[i][0];
            h = max(h, books[i][1]);
            if(w <= width)
                rtn = min(rtn, helper(books, width, i + 1) + h);
        }
        return mem[cur] = rtn;
        // helper(cur) = f(cur, cur + 1, cur + 2, ...)
    }
    vector<int> mem;
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        mem.resize(books.size() + 1, -1);
        mem.back() = 0;
        return helper(books, shelfWidth, 0);
    }
};

/*
 *  根據上面的解法改成 bottom-up tabulation
 *
 *  time  : O(N^2)
 *  space : O(N)
 */
class Solution {
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int sz = books.size();
        vector<int> dp(sz + 1);
        for(int i = sz - 1; i >= 0; --i) {
            int rtn{INT_MAX}, w{}, h{};
            for(int j = i; j < sz && w <= shelfWidth; ++j) {
                w += books[j][0];
                h = max(h, books[j][1]);
                if(w <= shelfWidth)
                    rtn = min(rtn, dp[j + 1] + h);
            }
            dp[i] = rtn;
        }
        return dp.front();
    }
};
