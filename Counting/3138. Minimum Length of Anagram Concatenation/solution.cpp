/*  除了暴力比對好像沒其他辦法?
 *  因為vector相同大小可以比對，所以先統計出第一個之後跟第一個比對
 *
 *  time  : O(N + KN), N : size of s, K : size of possible_ans
 *  space : O(K)
 */
class Solution {
public:
    int minAnagramLength(string s) {
        vector<int> possible_ans;
        for(int i = 1; i < s.size(); ++i)
            if(s.size() % i == 0) possible_ans.push_back(i);
        for(auto& ans : possible_ans) {
            vector<int> st(26);
            for(int i = 0; i < ans; ++i) st[s[i] - 'a']++;
            bool check{true};
            for(int i = 1; i * ans < s.size(); ++i) {
                vector<int> t(26);
                for(int j = i * ans; j < (i + 1) * ans; ++j)
                    t[s[j] - 'a']++;
                if(t != st) {
                    check = false;
                    break;
                }
            }
            if(check) return ans;
        }
        return s.size();
    }
};
/*  參考 : https://leetcode.cn/problems/minimum-length-of-anagram-concatenation/solutions/3014840/tong-wei-zi-fu-chuan-lian-jie-de-zui-xia-74z1/
 *  想法類似
 */
 class Solution {
public:
    int minAnagramLength(string s) {
        int n = s.size();
        auto check = [&](int m) -> bool {
            vector<int> count0(26);
            for (int j = 0; j < n; j += m) {
                vector<int> count1(26);
                for (int k = j; k < j + m; k++) {
                    count1[s[k] - 'a']++;
                }
                if (j > 0 && count0 != count1) {
                    return false;
                }
                count0.swap(count1);
            }
            return true;
        };
        for (int i = 1; i < n; i++) {
            if (n % i != 0) {
                continue;
            }
            if (check(i)) {
                return i;
            }
        }
        return n;
    }
};
