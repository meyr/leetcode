/* ref : https://leetcode.com/problems/sum-of-scores-of-built-strings/solutions/1907088/c-naive-hashing-by-honey1234-2psl/
 *
 */
class Solution {
public:
    long long sumScores(string s) {
        int m = 1e9 + 7, sz = s.size(), hash1{}, hash2{};
        long long ans{}, pk{1}, p{131};
        for(int i = 0, j = sz - 1; i < sz; ++i, --j) {
            hash1 = (hash1 + s[i] * pk) % m;
            pk = (p * pk) % m;
            hash2 = (s[j] + p * hash2) % m;
            if(hash1 == hash2) {
                ans += i + 1;
            } else {                                        // 當不符合的時候 使用傳統方法比對 居然可以過
                size_t left = 0, right = j;
                while(right < sz && s[left] == s[right])
                    ++left, ++right;
                ans += left;
            }
        }
        return ans;
    }
};
/*
    b, a, b, a, b
    b       = b * p^0 = h1
    b, a    = b * p^0 + a * p^1 = h1 + a * p^1
    b, a, b = b * p^0 + a * p^1 + b * p^2 = h2 + b * p^2;

    b       = b * p^0 = h1
    a, b    = a * p^0 + b * p^1 = a*p^0 + p * h1 = h2
    b, a, b = b * p^0 + a * p^1 + b * p^2 = b * p^0 + p * h2

    z
    az
    zaz
    bzaz
    zbzaz
    azbzaz      --> a, az, azb(O), azbz, azbza, azbzaz
    bazbzaz
    zbazbzaz
    azbazbzaz

*/
