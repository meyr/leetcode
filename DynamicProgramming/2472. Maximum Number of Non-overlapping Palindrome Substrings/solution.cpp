/*
 *      切個s成數個substring set
 *      其中每個substring都是palindrome且長度大於等於k
 *      回傳此set最多數量
 *
 *      使用dynamic programming 每到一個index就有兩個選項 一個是不選 helper(s, idx + 1)
 *                                                        一個是選擇 並且從mp中挑下一個idx 只要是palindrome且length >= k 才可以往後跳
 *
 *      time  : O(N^2)
 *      space : O(N)
 */
class Solution {
    unordered_map<char, vector<int>> mp;
    vector<int> offset;
    int k;
    bool isPalindrome(string_view s, int i, int j) {
        for(; i < j; ++i, --j)
            if(s[i] != s[j])
                return false;
        return true;
    }
    int helper(string_view s, int idx) {
        if(~mem[idx]) return mem[idx];
        int rtn = helper(s, idx + 1);
        auto& ref = mp[s[idx]];
        int i = offset[idx];
        for(int j = i + 1; j < ref.size(); ++j)
            if(ref[j] - ref[i] + 1 >= k && isPalindrome(s, ref[i], ref[j]))
                rtn = max(rtn, helper(s, ref[j] + 1) + 1);
        return mem[idx] = rtn;
    }
    vector<int> mem;
public:
    int maxPalindromes(string s, int k) {
        if(k == 1) return s.size();
        if(k == s.size()) return isPalindrome(s, 0, s.size() - 1);
        for(int i = 0; i < s.size(); ++i) {
            mp[s[i]].push_back(i);
            offset.push_back(mp[s[i]].size() - 1);
        }
        this->k = k;
        mem.resize(s.size() + 1, -1);
        mem.back() = 0;
        return helper(s, 0);
    }
};
