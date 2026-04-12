/*  一開始寫出的版本會TLE又MLE
 *
 */
class Solution {
    unordered_map<char, vector<int>> um{
        {'A', {0, 0}}, {'B', {0, 1}}, {'C', {0, 2}}, {'D', {0, 3}}, {'E', {0, 4}}, {'F', {0, 5}},
        {'G', {1, 0}}, {'H', {1, 1}}, {'I', {1, 2}}, {'J', {1, 3}}, {'K', {1, 4}}, {'L', {1, 5}},
        {'M', {2, 0}}, {'N', {2, 1}}, {'O', {2, 2}}, {'P', {2, 3}}, {'Q', {2, 4}}, {'R', {2, 5}},
        {'S', {3, 0}}, {'T', {3, 1}}, {'U', {3, 2}}, {'V', {3, 3}}, {'W', {3, 4}}, {'X', {3, 5}},
        {'Y', {4, 0}}, {'Z', {4, 1}}
    };
    int getDist(const char& a, const char& b) 
    {
        return abs(um[b][0] - um[a][0]) + abs(um[b][1] - um[a][1]);
    }
    int helper(const string& word, int i, int j, int k)
    {
        int rtn;
        if(~mem[i][j][k]) return mem[i][j][k];
        
        if(k == word.size()) rtn = 0;
        else {
            rtn = min(
                getDist(word[i], word[k]) + helper(word, k, j, k + 1),
                getDist(word[j], word[k]) + helper(word, i, k, k + 1)
            );
        }
        return mem[i][j][k] = rtn;
    }
    vector<vector<vector<int>>> mem;
    vector<int> pfs;
public:
    int minimumDistance(string word) {
        int sz = word.size();
        int ans = INT_MAX;
        // 這邊使用太大的記憶體 因為O(N^3)
        // 不需要知道前一個位置 只需要知道前一個char 這樣可以降成O(27*27*N) = O(N)
        mem.resize(sz + 1, vector<vector<int>>(sz + 1, vector<int>(sz + 1, -1)));
        pfs.resize(sz);
        for(int i = 1; i < sz; ++i)
            pfs[i] = pfs[i - 1] + getDist(word[i - 1], word[i]);
        // 這邊會造成TLE 因為列舉所有finger 2的位置會變成O(N * N^3) = O(N^4)
        // 只要定義兩根手指都是從懸空開始
        for(int j = 1; j < sz; ++j)
            ans = min(ans, pfs[j - 1] + helper(word, j - 1, j, j + 1));
        return ans;
    }
};
/*  根據gemini的答案，修正原本的source code之後
 */
 class Solution {
    // 這邊不需要用map因為六個一列 所以char變成offset之後
    // y = offset / 6, x = offset % 6 之後就可以進行運算
    unordered_map<char, vector<int>> um{
        {'A', {0, 0}}, {'B', {0, 1}}, {'C', {0, 2}}, {'D', {0, 3}}, {'E', {0, 4}}, {'F', {0, 5}},
        {'G', {1, 0}}, {'H', {1, 1}}, {'I', {1, 2}}, {'J', {1, 3}}, {'K', {1, 4}}, {'L', {1, 5}},
        {'M', {2, 0}}, {'N', {2, 1}}, {'O', {2, 2}}, {'P', {2, 3}}, {'Q', {2, 4}}, {'R', {2, 5}},
        {'S', {3, 0}}, {'T', {3, 1}}, {'U', {3, 2}}, {'V', {3, 3}}, {'W', {3, 4}}, {'X', {3, 5}},
        {'Y', {4, 0}}, {'Z', {4, 1}}
    };
    int getDist(int a, char b) // 注意: 一個是offset 一個是char
    {
        if(a == 26) return 0; // 從懸空到按第一個char不需要成本
        else {
            return abs(um[b][0] - um[a + 'A'][0]) + abs(um[b][1] - um[a + 'A'][1]);
        }
    }
    int helper(const string& word, int i, int j, int k)
    {
        int rtn;
        if(~mem[i][j][k]) return mem[i][j][k];

        if(k == word.size()) rtn = 0;
        else {
            rtn = min(
                getDist(i, word[k]) + helper(word, word[k] - 'A', j, k + 1),
                getDist(j, word[k]) + helper(word, i, word[k] - 'A', k + 1)
            );
        }
        return mem[i][j][k] = rtn;
    }
    vector<vector<vector<int>>> mem;
public:
    int minimumDistance(string word) {
        int sz = word.size();
        int ans = INT_MAX;
        // 只需紀錄1st finger和2nd finger分別按到哪個char
        mem.resize(27, vector<vector<int>>(27, vector<int>(sz + 1, -1)));
        return helper(word, 26, 26, 0);
    }
};
