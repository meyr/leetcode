/*

idx        0, 1, 2, 3, 4, 5, 6, 7, 8
string     1, 1, 0, 0, 0, 1, 0, 0, 1    <-- 先把前後加上1

        g-0-1 : 0, 1                    針對每個屬性進行分類
        g-2-0 : 2, 3, 4
        g-5-1 : 5
        g-6-0 : 6, 7
        g-8-1 : 8

    pattern 1-0-1-0-1 --> 1-1-1-1-1     因為 0-1-0 的pattern會變成 0-0-0 且 1-0-0-0-1 會變成 1-1-1-1-1
                                        所以找出1-0-1-0-1的pattern 並且轉換成 1-1-1-1-1 看哪一個pattern會得到最多的1


   time  : O(N)
   space : O(N)

 */
class Solution {
    bool valid(vector<pair<int, int>>& groups, int idx) {
        if(groups[idx    ].first == 1 &&
           groups[idx - 1].first == 0 &&
           groups[idx - 2].first == 1 &&
           groups[idx - 3].first == 0 &&
           groups[idx - 4].first == 1) return true;
        else return false;
    }
    int sum(vector<pair<int, int>>& groups, int idx) {
        int rtn{};
        for(int i = 0; i < 5; ++i)
            rtn += groups[idx - i].second;
        return rtn;
    }
public:
    int maxActiveSectionsAfterTrade(string s) {
        s += '1';
        vector<pair<int, int>> groups; // priority(1/0), count
        groups.push_back({1, 1});
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] - '0' == groups.back().first) groups.back().second++;
            else groups.push_back({s[i] - '0', 1});
        }
        vector<int> back(groups.size());
        for(int i = back.size() - 2; i >= 0; --i) {
            back[i] = back[i + 1] + (groups[i + 1].first == 1 ? groups[i + 1].second : 0);
        }

        int rtn{};
        if(groups.size() < 5) {
            for(auto& ref : groups)
                rtn += ref.first == 1 ? ref.second : 0;
        } else {
            int pre{};
            for(int i = 4; i < groups.size(); ++i)
                if(valid(groups, i)) {// 1, 0, 1, 0, 1
                    rtn = max(rtn, pre + sum(groups, i) + back[i]);
                pre += groups[i - 4].first == 1 ? groups[i - 4].second : 0;
            }
        }

        return rtn - 2;
    }
};
/*  參考官方解答 https://leetcode.com/problems/maximize-active-section-with-trade-i/solutions/8402217/maximize-active-section-with-trade-i-by-ox02o/
 *
 *  考慮以下pattern  1000110001  因為根據操錯作 1000110001 --> 1000 00 0001 --> 1 111 11 111 1
 *  所以只要找出兩個相鄰的zero group 總和為最大 加上 原本的 1 的個數 就是答案
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        int cnt1 = count(s.begin(), s.end(), '1');  // 計算所有1的個數

        vector<int> zeroBlocks; // 每個連續0的個數
        int i = 0;
        while (i < n) {
            int start = i;

            while (i < n && s[i] == s[start]) {
                ++i;
            }

            if (s[start] == '0') {
                zeroBlocks.push_back(i - start);
            }
        }

        int m = zeroBlocks.size();

        if (m < 2) {
            return cnt1;
        }

        int bestGain = 0;  // Optimal Increment
        for (int i = 0; i < m - 1; ++i) {
            bestGain = max(bestGain, zeroBlocks[i] + zeroBlocks[i + 1]);    // 找出相鄰兩個zero block總和為最大
        }

        return cnt1 + bestGain;
    }
};
/*  根據上面的想法自己寫了一次
 *
 */
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int total{};
        for(const auto& c : s) total += c - '0';
        s += '1';
        vector<int> zeroBlock;
        int start = 0;
        for(int i = 0; i < s.size(); ++i) {
            while(i < s.size() && s[i] == s[start]) i++;
            if(s[start] == '0') zeroBlock.push_back(i - start);
            start = i;
        }
        if(zeroBlock.size() < 2) return total;
        int maxv{};
        for(int i = 1; i < zeroBlock.size(); ++i)
            maxv = max(maxv, zeroBlock[i] + zeroBlock[i - 1]);
        return maxv + total;
    }
};
/* 合併兩個for loop變成一個for loop
 */
class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int total{};
        for(const auto& c : s) total += c - '0';
        s += '1';
        vector<int> zeroBlock;
        int start = 0, rtn = total;
        for(int i = 0; i < s.size(); ++i) {
            while(i < s.size() && s[i] == s[start]) i++;
            if(s[start] == '0') {
                zeroBlock.push_back(i - start);
                int sz = zeroBlock.size();
                if(sz > 1)
                    rtn = max(rtn, zeroBlock[sz - 2] + zeroBlock[sz - 1] + total);
            }
            start = i;
        }
        return rtn;
    }
};
/*
 * 因為zero block只參考最後兩個 所以不需要使用vector
 * 這樣space complexity 可以變成O(1)
 */
