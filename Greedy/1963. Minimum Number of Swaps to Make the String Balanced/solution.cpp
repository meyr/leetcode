/* Greedy point : 因為要找出最少的swap，所以最有效率的swap是swap一次可以產生兩組正確的closing brackets 
 * 例如: ]]][[[
 *       [1]]][[  (bad answer)
 *       [[1][2][  (good answer)
 * 所以找出mismatch的個數 ， 答案就是 (mismatch + 1) / 2
 *
 * time  : O(N)
 * space : O(N)
 */
class Solution {
public:
    int minSwaps(string s) {
        stack<char> st;
        int mismatch{};
        for(auto& c : s) {
            if(c == '[') st.push(c);
            else {
                if(!st.empty()) st.pop();
                else mismatch++;
            }
        }
        return (mismatch + 1) / 2;        
    }
};

