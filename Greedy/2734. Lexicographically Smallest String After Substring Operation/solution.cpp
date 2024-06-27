/*
 *  需要做一次操作 選擇一個subarray然後每個char - 1, 'a'的話就是'z'
 *  因為結果要 lexicographically smallest 所以除了'a'以外都要做是最好的
 *  但是只能選一個subarray 所以選擇第一個非'a'開頭的subarray 直到下一個'a'
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    string smallestString(string s) {
        int st{};
        while(st < s.size() && s[st] == 'a') st++;
        if(st == s.size()) s.back() = 'z';
        for(;st < s.size() && s[st] != 'a'; ++st)
            s[st]--;
        return s;
    }
};
