/*
 *   使用兩個pointer來對version做parse
 *   必須注意pointer必須往前 否則會卡在'.'
 *
 *   time  : O(N + M)
 *   space : O(1)
 */
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int sz1 = version1.size(), sz2 = version2.size();
        int i = 0, j = 0;
        while(i < sz1 || j < sz2) {
            int val1{}, val2{};
            while(i < sz1 && version1[i] != '.') val1 = val1 * 10 + (version1[i++] - '0');
            while(j < sz2 && version2[j] != '.') val2 = val2 * 10 + (version2[j++] - '0');
            if(val1 > val2) return 1;
            else if(val1 < val2) return -1;
			i++, j++; // __important__否則i和j會停在'.'
        }
        return 0;
    }
};
