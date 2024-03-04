/*
 *  參考lee215解答 https://leetcode.com/problems/bag-of-tokens/solutions/197696/c-java-python-greedy-two-pointers/
 *  
 *  這一題我怎麼寫都寫不好
 *  因為題目的要求是最大化score 所以Greedy point就是__只要有power就換score__
 *  當power < tokens[i] 就看看有沒有score換最大的tokens[j]回來
 */

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        sort(begin(tokens), end(tokens)); // O(NlogN)
        int res{}, points{}, i = 0, j = tokens.size() - 1;
        while(i <= j) { // O(N)
            if(power >= tokens[i]) { // 有power就換score 1
                power -= tokens[i++];
                res = max(res, ++points);
            } else if(points > 0) { // power不夠 用score換power 
                points--;
                power += tokens[j--]; 
            } else break;
        }
        return res;

        // time  : O(NlogN + N) = O(NlogN)
        // space : O(logN) 
    }
};
