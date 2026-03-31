/*  ref : https://leetcode.com/problems/lexicographically-smallest-generated-string/solutions/7717206/lexicographically-smallest-generated-str-fnmj/
 *
 *  參考官方解答
 *  自己寫寫不好的原因是 沒好好理解題目 和 沒好好理解條件
 *  str1[i] = 'T' 意思是 str1[i ... i + m - 1] = str2 這些位置是固定的 不能再修改
 *  剩下的就是可以修改的index
 *
 *  time  : O(NM + NM) = O(NM)
 *  space : O(N + M)
 */
class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        string s(n + m - 1, 'a');
        vector<int> fixed(n + m - 1, 0);        // 標記不能修改的index
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = i; j < i + m; j++) {
                    if (fixed[j] && s[j] != str2[j - i]) {  // 如果不能修改 且 str1[j] != str2[j - i] 表示違反題意 返回空字串
                        return "";
                    } else {
                        s[j] = str2[j - i];         // 因為str1[i] == 'T' 所以填入str2且標記為不能修改
                        fixed[j] = 1;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {   // 檢查F的部分
            if (str1[i] == 'F') {
                bool flag = false;      // 表示有一個index和str2不一樣
                int idx = -1;           // __importatn__ 因為要 lexicographically smallest string 所以__從最後面__開始找 找到不是fixed可以修改的index
                for (int j = i + m - 1; j >= i; j--) {
                    if (str2[j - i] != s[j]) {
                        flag = true;
                    }
                    if (idx == -1 && !fixed[j]) { // idx == -1 (還沒找到) 且 !fixed[j](可以修改) 就把idx設為j
                        idx = j;
                    }
                }
                if (flag) { // 本來就不一樣 所以不用修改
                    continue;
                } else if (idx != -1) { // 和str2一樣 所以需要修改 且__有找到__可以修改的位置
                    s[idx] = 'b';
                } else {                // 和str2一樣 所以需要修改 但__找不到__可以修改的位置
                    return "";
                }
            }
        }
        return s;
    }
};
