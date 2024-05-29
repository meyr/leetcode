/*
 *  參考: https://leetcode.com/problems/number-of-steps-to-reduce-a-number-in-binary-representation-to-one/solutions/564290/simple-c-code-by-char-counting/
 *
 *
 */

class Solution {
public:
    int numSteps(string s) {
        int step{};
        while(s != "1") {
            if(s.back() == '0') { // 因為0就是一直除2 step+1
                s.pop_back();
                step++;
            } else {
                while(!s.empty() && s.back() == '1') { // odd 會進行+1 看己個1會一直進位最後也是pop掉 因為除2
                    s.pop_back();
                    step++;
                }
                if(s.empty()) return step + 1; // 加到超過 必須多除一次 所以step + 1
                else {
                    s.back() = '1'; // 進位除2後剩下的1
                    step++;
                }
            }
        }
        return step;
    }
};
