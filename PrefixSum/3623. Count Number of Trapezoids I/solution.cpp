/*  統計相同y的點數
 *  vector<int> cnt : 計算N取2的數值
 *  vector<int> pfs : 計算cnt的prefix sum
 *
 *  time  : O(N + N + N + N) = O(N)
 *  space : O(N + N + N) = O(N)
 */
class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int mod = 1e9 + 7;
        unordered_map<int, int> um;
        for(auto& point : points)
            um[point[1]]++;
        vector<int> cnt;
        for(auto& ref : um) {
            long long n = ref.second;
            cnt.push_back((n * (n - 1) / 2) % mod);
        }
        vector<int> pfs(cnt.size() + 1);
        for(int i = 1; i < cnt.size(); ++i)
            pfs[i] = (pfs[i - 1] + (long long)cnt[i - 1]) % mod;
        long long ans{};
        for(int i = cnt.size() - 1; i >= 0; --i)
            ans = (ans + (long long)cnt[i] * pfs[i]) % mod;
        return ans % mod;
    }
};
/*
    0 : 3
    2 : 2

    Cn2 = N!*(n-1)!/2!
*/
