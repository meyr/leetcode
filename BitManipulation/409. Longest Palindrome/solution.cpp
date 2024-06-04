/*
 *  因為要組成palindrome等於是數每個char的個數 偶數就可以使用
 *
 *  time  : O(N)
 *  space : O(1)
 */

class Solution {
public:
    int longestPalindrome(string s) {
        int ans{}, lower{}, upper{};
        for(auto& c : s) {
            if(c >= 'a') {
                if((lower >> (c - 'a')) & 1)
                    ans += 2;
                lower ^= 1 << (c - 'a');
            } else {
                if((upper >> (c - 'A')) & 1)
                    ans += 2;
                upper ^= 1 << (c - 'A');
            }
        }
        return ans += lower != 0 || upper != 0;
    }
};


/*
 *   或是可以用bitset
 */

class Solution {
public:
    int longestPalindrome(string s) {
        int ans{};
        bitset<26> lower{}, upper{};
        for(auto& c : s) {
            if(c >= 'a') {
                if(lower[c - 'a'])
                    ans += 2;
                lower.flip(c - 'a');
            } else {
                if(upper[c - 'A'])
                    ans += 2;
                upper.flip(c - 'A');
            }
        }
        return ans += lower != 0 || upper != 0;
    }
};
