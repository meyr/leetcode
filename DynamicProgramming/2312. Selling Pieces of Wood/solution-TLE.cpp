class Solution {
    long long helper(int m, int n, vector<vector<int>>& prices) {
        if(~mem[m][n]) return mem[m][n];
        long long ans{};
        for(auto& pr : prices) {
            int h = pr[0], w = pr[1], p = pr[2];
            if(h <= m && w <= n) {
                long long tmp = max(helper(h, n - w, prices) + 
                                    helper(m - h, n, prices), 
                                    helper(m, n - w, prices) + 
                                    helper(m - h, w, prices)) + p;
                ans = max(ans, tmp);
            }
        }
        return mem[m][n] = ans;
    }
    vector<vector<long long>> mem;
public:
    long long sellingWood(int m, int n, vector<vector<int>>& prices) {
        mem.resize(m + 1, vector<long long>(n + 1, -1));
        for(int i = 0; i < m; ++i)
            mem[i][0] = 0;
        for(int i = 0; i < n; ++i)
            mem[0][i] = 0;
        return helper(m, n, prices);
    }
};

/*
       w 
    -------------
 h  |    |       |
    |____|.......|      m
    |____________|
           n

       w 
    -------------
 h  |    |       |
    |____|       |      m
    |____._______|
           n
*/
