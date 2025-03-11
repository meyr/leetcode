/*  怎麼寫都錯 所以參考解答
 *  https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/solutions/516977/javacpython-easy-and-concise-by-lee215-od5j/
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int numberOfSubstrings(string s) {
        int count[3] = {}, rtn{}, total{};
        for(int left = 0, right = 0; right < s.size(); ++right) {
            if(count[s[right] - 'a']++ == 0) total++;
            while(total == 3) {
                if(count[s[left] - 'a']-- == 1) total--;
                left++;
            }
            rtn += left;    // __important__ 當left != 0, 表示有使用過上面的while, 表示有找到都有abc的字串
                            //                            之後每次新增一個char, 之前重複的答案會在出現一次
        }
        return rtn;
    }
};
/*
        0, 1, 2, 3, 4, 5, 6
        a, c, b, b, c, a, c
        l     r                 找到acb
           l  r                 while loop 之後cb, 但是  acb符合
           l     r              雖然cbb 不符合,    但是 accb符合
           l        r           雖然cbbc不符合,    但是acbbc符合
           l           r        找到cbbca
                    l  r        while loop 之後ca, 但是bca,  bbca,  cbbca,  acbbca 符合
                    l     r     雖然cac 不符合,    但是bcac, bbcac, cbbcac, acbbcac符合  
*/
