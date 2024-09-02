/*
 *   因為答案只有兩種'F', 'T'
 *   分別針對這兩種作slinding window看哪一種的結果最大
 *
 *   time  : O(N)
 *   space : O(1)
 */
class Solution {
    int helper(string& answerKey, int k, const char c) {
        int left{}, right{}, cnt{}, ans{};
        for(int left = 0, right = 0, cnt = 0; right < answerKey.size(); ++right) {
            cnt += answerKey[right] == c;
            while(cnt > k) 
                cnt -= answerKey[left++] == c;
            ans = max(ans, right - left + 1);
        }     
        return ans;
    }
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        return max(helper(answerKey, k, 'T'), helper(answerKey, k, 'F'));
    }
};
