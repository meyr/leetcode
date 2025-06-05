/*  因為每個字母對應會形成一個group 且group中會以字母最小的為代表 這樣才可以達到 lexicographically smallest equivalent string
 *  所以使用union find中root的概念
 *  
 *  time  : O(N + M)
 *  space : O(1)
 *
 */
class Solution {
    vector<int> table;
    int find(int x) {
        if(table[x] == x) return x;
        else return table[x] = find(table[x]);
    }
    void connect(int i, int j) {
        i = find(i), j = find(j);
        if(i == j) return;
        if(i > j) swap(i, j);
        table[j] = i;
    }
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        table.resize(26);
        iota(begin(table), end(table), 0);
        for(int i = 0; i < s1.size(); ++i)
            connect(s1[i] - 'a', s2[i] - 'a');
        for(auto& c : baseStr)
            c = table[find(c - 'a')] + 'a';
        return baseStr;
    }
};
