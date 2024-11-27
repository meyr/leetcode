/* 使用string來比較 效率比較差 即使使用了string_view
 *
 */
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        string str_colors{}, tg1{"1"}, tg2{"0"};
        for(int i = 0; i < colors.size(); ++i) str_colors += to_string(colors[i]);
        for(int i = 0; i < k; ++i) str_colors += to_string(colors[i]);
        for(int i = 1; i < k; ++i) {
            tg1 += to_string((i + 1) % 2);
            tg2 += to_string(i % 2);
        }
        int ans{};
        string_view sv{str_colors}; // 使用string_view來觀察str_colors可以避免不必要的string copy
        for(int i = 0; i < colors.size(); ++i) {
            if(sv.substr(i, k) == tg1) ans++;
            if(sv.substr(i, k) == tg2) ans++;
        }
        return ans;
    }
};
/*  改用prefix sum來表示不連續01的個數
 *
 *  0, 1, 0, 1, 0, 0, 1  <-- colors
 *  1, 2, 3, 4, 5, 1, 2  <-- pfs
 *        *  *  *
 *
 *  time  : O(K + N + N) = O(N + K)
 *  space : O(N + K)
 */
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        for(int i = 0; i < k - 1; ++i) colors.push_back(colors[i]);
        vector<int> pfs(colors.size());
        pfs[0] = 1;
        for(int i = 1; i < colors.size(); ++i) {
            if(colors[i] != colors[i - 1]) pfs[i] = pfs[i - 1] + 1;
            else pfs[i] = 1;
        }
        int ans{};
        for(int i = k - 1; i < pfs.size(); ++i) {
            ans += pfs[i] - pfs[i - k + 1] == k - 1;
        }
        return ans;
    }
};
/*  根據上面的solution可以省略把k-1個colors放到後面
 *  並且合併兩個for loop
 *
 *  time  : O(N)
 *  space : O(N+K) --> 使用queue可以變成 O(K)
 */
class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k) {
        int sz = colors.size(), ans{};
        vector<int> pfs(sz + k - 1);
        pfs[0] = 1;
        for(int i = 1; i < sz + k - 1; ++i) {
            pfs[i] = colors[i % sz] != colors[(i + sz - 1)% sz] ? pfs[i - 1] + 1 : 1;
            ans += i >= k - 1 ? pfs[i] - pfs[i - k + 1] == k - 1 : 0;
        }
        return ans;
    }
};
