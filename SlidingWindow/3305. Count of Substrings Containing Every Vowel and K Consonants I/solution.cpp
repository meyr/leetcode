/*   參考3306解法
 *   但是一直無法理解這個解法 interview遇到這題應該也是寫不出來
 */
class Solution {
    unordered_map<char, int> vowel{{'a', 0}, {'e', 1}, {'i', 2}, {'o', 3}, {'u', 4}};
    int helper(string& word, int k) {
        int rtn{}, cons{};
        int cnt[5] = {};
        for(int left = 0, right = 0; right < word.size(); ++right) {
            char& c = word[right];
            if(vowel.count(c)) cnt[vowel[c]]++;
            else cons++;
            while(cnt[0] && cnt[1] && cnt[2] && cnt[3] && cnt[4] && cons > k) {
                char& c = word[left++];
                if(vowel.count(c)) cnt[vowel[c]]--;
                else cons--;
            }
            rtn += right - left + 1;
        }
        return rtn;
    }
public:
    int countOfSubstrings(string word, int k) {
        return helper(word, k) - helper(word, k - 1);
    }
};
/*  參考 : https://leetcode.cn/problems/count-of-substrings-containing-every-vowel-and-k-consonants-i/solutions/3077748/yuan-yin-fu-yin-zi-fu-chuan-ji-shu-i-by-r8rjy/
 *  使用暴力破解 但是時間複雜度太高 但不失為一個解法
 *  這邊是固定left 增加right 好處是substring都是從小到大 比較好計算
 */
class Solution {
    unordered_set<char> vowel = {'a', 'e', 'i', 'o', 'u'};
public:
    int countOfSubstrings(string word, int k) {
        int sz = word.size(), ans{};
        for(int left = 0; left < word.size() - 5 - k + 1; ++left) {
            unordered_set<char> occur;
            int cons{};
            for(int right = left; right < sz; ++right) {
                if(vowel.count(word[right])) occur.insert(word[right]);
                else cons++;
                if(vowel.size() == occur.size() && cons == k) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
/*  參考 : https://github.com/wisdompeak/LeetCode/tree/master/Two_Pointers/3306.Count-of-Substrings-Containing-Every-Vowel-and-K-Consonants-II 
 *  
 *  time : O(N)
 *  space: O(N)
 */
class Solution {
    unordered_map<char, int> vowel{{'a', 0}, {'e', 1}, {'i', 2}, {'o', 3}, {'u', 4}};
public:
    int countOfSubstrings(string word, int k) {
        int vs = 0;
        int cons = 0;
        int sz = word.size();

        unordered_map<char,int> Map;

        vector<int> consecutive(sz); // 統計index之後連續vowel有多少個
        int c = 0;
        for (int i = sz - 1; i >= 0; i--) {
            if (vowel.count(word[i])) c++;
            else c = 0;
            consecutive[i] = c;
        }

        long long ret = 0;
        for (int left = 0, right = 0; left < sz; left++) {
            // 移動right找出滿足條件的substring
            while (right < sz && (vs < 5 || cons < k)) { // 停止條件 vs == 5 && cons >= k 所以if loop還要再檢查一次, right == sz 已經找到word盡頭
                char& c = word[right++];    // __important__ 因為這邊right++ 所以right會在成立條件的下一個char
                if (vowel.count(c)) {
                    if (++Map[c] == 1) vs++;
                } else cons++;
            }

            // 因為 every vowel at least once 所以加上consecutive[right]
            if (vs == 5 && cons == k)
                ret += 1 + (right < sz ? consecutive[right] : 0);
            //        ^^ right結尾在條件成立的下一個char, 所以必須+1包括上一個, 也有可能是right == sz

            // left 向右移動一格
            char& c = word[left];
            if (vowel.count(c)) {
                if (--Map[c]==0) vs--;
            } else cons--;
        }
        return ret;

    }
};
