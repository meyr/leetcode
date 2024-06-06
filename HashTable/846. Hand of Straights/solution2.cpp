/*
 *  參考 : https://leetcode.com/problems/hand-of-straights/solutions/135598/c-java-python-o-mlogm-complexity/
 *
 *  概念和第一個想法類似 但是lee215寫得更精簡 並且不需要erase
 */

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        map<int, int> m;
        for(auto& n : hand) m[n]++;
        for(auto& ref : m) {
            if(ref.second > 0) {
                for(int i = groupSize - 1; i >= 0; --i) { // ** i >= 0 的最後一筆是把ref.second也清掉
                    m[ref.first + i] -= m[ref.first]; // **因為ref.second的個數表示至少這麼多group 一次處理
                    if(m[ref.first + i] < 0)
                        return false;
                }
            }
        }
        return true;
    }
};
