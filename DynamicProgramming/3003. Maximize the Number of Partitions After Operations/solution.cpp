/*  題目提到要得到最大分割 且每一次分割只要滿足 distinct char <= k, 
 *  根據貪婪法 應該是全部都切成1char的substring, 就會有最大切割
 *
 *  不過根據參考解答 https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/solutions/4520834/c-java-python-clean-bitmask-dp-by-tojuna-da9a/
 *  切割的條件應該是 substring達到 distinct char == k 才可以切割
 *
 */
class Solution {
public:
    unordered_map<long long, int> cache;
    string s;
    int k;

    int maxPartitionsAfterOperations(string s, int k) {
        this->s = s;
        this->k = k;
        return dp(0, 0, true) + 1;
    }

private:
    int dp(long long index, long long currentSet, bool canChange) {
        long long key = (index << 27) | (currentSet << 1) | canChange;
        if (cache.count(key)) return cache[key];
        if (index == s.size()) return 0;

        int characterIndex = s[index] - 'a';
        int currentSetUpdated = currentSet | (1 << characterIndex);
        int distinctCount = __builtin_popcount(currentSetUpdated);

        // res為不替換的結果
        int res;
        if (distinctCount > k) // 達到distinctCount == k 所以切割，currentSet = 1 << characterIndex, 全新的一個substring
            res = 1 + dp(index + 1, 1 << characterIndex, canChange);
        else  // 繼續收集
            res = dp(index + 1, currentSetUpdated, canChange);

        if (canChange) { // 從a~z選一個字母替換目前的index
            for (int newCharIndex = 0; newCharIndex < 26; ++newCharIndex) {
                int newSet = currentSet | (1 << newCharIndex);
                int newDistinctCount = __builtin_popcount(newSet);

                if (newDistinctCount > k) {
                    res = max(res, 1 + dp(index + 1, 1 << newCharIndex, false)); // 替換，和不替換的結果取最大值
                } else {
                    res = max(res, dp(index + 1, newSet, false));
                }
            }
        }

        return cache[key] = res;
    }
};
