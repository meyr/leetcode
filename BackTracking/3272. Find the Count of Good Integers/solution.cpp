/*  參考: https://leetcode.com/problems/find-the-count-of-good-integers/solutions/6641380/naruto-step-by-step-simple-easiest-expla-j7zi/
 *
 */
class Solution {
public:
    // 計算n!
    long long factorial(int num) {
        long long chakra = 1;
        for (int i = 1; i <= num; i++) chakra *= i;
        return chakra;
    }

    // 使用backtracking 得到所有的k-palindrome字串
    void generatePalindromes(string& clone, int index, vector<string>& validClones, int k) {
        if (index >= (clone.length() + 1) / 2) { // clone.size() === 7 --> 7+1/2 = 4
                                                 // 3 --> 2
                                                 // 4 --> 2 
                                                 // 5 --> 3   所以 (n+1)/2  只要超過palindrome的中間即可停止 
            if (stoll(clone) % k == 0) validClones.push_back(clone);
            return;
        }

        for (char c = index == 0 ? '1' : '0'; c <= '9'; c++) {
            clone[index] = c;
            clone[clone.size() - 1 - index] = c;
            generatePalindromes(clone, index + 1, validClones, k);
        }
    }

    long long countGoodIntegers(int n, int k) {
        vector<string> validClones;
        string baseClone(n, '0'); // n = 3 --> baseClone = "000"
                                  //               index = 0,1,2
        generatePalindromes(baseClone, 0, validClones, k);

        set<string> chakraPatterns;

        // 因為validClones 會出現 1551, 5115 但是這兩個排列出來的結果是一樣的 必須合併
        for (auto& clone : validClones) {   
            vector<int> freq(10, 0);    // '0'~'9'出現的次數
            for (char c : clone) freq[c - '0']++;
            string pattern;
            for (int f : freq) pattern += (char)('a' + f); // 拚出一個特別的pattern 來代表'0'~'9'出現的次數
            chakraPatterns.insert(pattern);                //    例如: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
                                                           //          0, 0, 0, 1, 2, 2, 0, 0, 0, 0
        }                                                  // pattern  a, a, a, b, c, c, a, a, a, a ==> "aaabccaaaa"

        long long basePerms = factorial(n); //計算n!
        long long total = 0;

        for (auto& pattern : chakraPatterns) {
            long long perms = basePerms;
            for (char f : pattern) perms /= factorial(f - 'a'); //計算 n!/freq[d0]! * freq[d1]! * ...

            if (pattern[0] != 'a') { // 當pattern有'0'在裡面的情況，上面的公式需要修正
                int zeros = pattern[0] - 'a' - 1;
                long long zeroPerms = factorial(n - 1); // 第一個是'0'其他繼續排列 所以是
                                                        // (n-1)! / freq[d0 - 1]! * freq[d1]! * ...
                for (int j = 1; j < pattern.size(); j++) zeroPerms /= factorial(pattern[j] - 'a');
                zeroPerms /= factorial(zeros);
                perms -= zeroPerms;
            }

            total += perms;
        }

        return total;
    }
};
/*
    如果每個數字都不一樣 則排列數為n!
    例如 : abc --> 3! = 6
        
           abc
           acb
           bac
           bca
           cab
           cba

           如果c == a, 因為a==c 所以有兩個空格可以排入 兩個空格的意思是2! 所以要除掉

           abc   --> aba  --
           acb   --> aab  **
           bac   --> baa  ==
           bca   --> baa  ==
           cab   --> aab  **
           cba   --> aba  --      

*/
/*  參考:https://leetcode.com/problems/find-the-count-of-good-integers/solutions/5716362/python-enumerate-and-combinations-by-lee-c9yy/
 *  想法和上面一樣 先列舉所有的palindrome 之後再檢查是否為k-palindrome並且排列過後的key沒看過 
 * 
 */
 class Solution {
    long long factorial(int num) {
        long long chakra = 1;
        for (int i = 1; i <= num; i++) chakra *= i;
        return chakra;
    }
public:
    long long countGoodIntegers(int n, int k) {
        int n2 = (n + 1) / 2;   // 只需要列舉palindromic的前半部即可
        long long res{};
        unordered_set<string> seen;
        for(int v = pow(10, n2 - 1); v < pow(10, n2); ++v) {
            string strv = to_string(v);
            string vv = strv + string(rbegin(strv), rend(strv)).substr(n % 2); // 組合成palindromic
            //      原本string   反轉原本的string               根據n來決定是否丟掉第一個char   
            string key(begin(vv), end(vv)); // key來判斷是否有處理過
            sort(begin(key), end(key));
            if(stoll(vv) % k == 0 and !seen.count(key)) {
                seen.insert(key);
                unordered_map<char, int> m;
                for(auto& c : vv) m[c]++;
                long long x = (n - m['0']) * factorial(n - 1); // __important__ (第一個數不取'0')*(剩下的數字排列)
                for(auto& ref : m)                             // 因為有重複的所以要除掉
                    x /= factorial(ref.second);
                res += x;
            }
        }
        return res;
    }
};
