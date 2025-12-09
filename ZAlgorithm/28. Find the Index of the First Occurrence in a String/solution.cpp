class Solution {
    vector<int> z_algorithm(string& s) {
        int sz = s.length(), left{}, right{};
        vector<int> z(sz);
        for (int i = 1; i < sz; i++) {
            if (i <= right) {
                int k = i - left;
                z[i] = min(right - i + 1, z[k]);
            }
            while (i + z[i] < sz && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] - 1 > right) {
                left = i;
                right = i + z[i] - 1;
            }
        }
        return z;
    }
public:
    int strStr(string haystack, string needle) {
        string newstr = needle + '$' + haystack;    // __important__ 把要尋找的string放在開頭 當成尋找longest common prefix
        vector<int> z = z_algorithm(newstr);
        int ans{};
        for(int i = needle.size() + 1; i < newstr.size(); ++i)
            if(z[i] == needle.size()) return i - needle.size() - 1; // 找到match pattern長度 計算原本的index
        return -1;
    }
};
