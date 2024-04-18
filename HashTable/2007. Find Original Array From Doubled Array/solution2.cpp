/*
 *  參考lee215的解答 : 
 *  https://leetcode.com/problems/find-original-array-from-doubled-array/solutions/1470959/java-c-python-match-from-the-smallest-or-biggest-100/
 *
 *  和我的solution的差別是 他是針對key做排序 time complexity會比較好一點 如果都不重複則 K == N
 *  time  : O(N + K + KlogK + K) = O(N + KlogK)
 *  space : O(K)
 */

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& A) {
        if (A.size() % 2) return {};
        unordered_map<int, int> c;
        for (int a : A) c[a]++;   // O(N)
        vector<int> keys;
        for (auto it : c)  // O(K)
            keys.push_back(it.first);
        sort(keys.begin(), keys.end()); //O(KlogK)
        vector<int> res;
        for (int x : keys) { // O(K)
            if (c[x] > c[2 * x]) return {}; // 個數不對
            for (int i = 0; i < c[x]; ++i, c[2 * x]--)
                res.push_back(x);
        }
        return res;
    }
};
