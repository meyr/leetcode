/*
     參考解答
     https://leetcode.com/problems/find-the-winner-of-an-array-game/solutions/768007/java-c-python-one-pass-o-1-space/

     因為遇到比較大的值那個值就會一直留著直到遇到下一個更大的值
     所以不需要紀錄之前遇到過的值, 因為最大值會一直留著所以一輪過後也是他會贏，
     所以不需要把data push_back到後面。

     time  : O(N)
     space : O(1)
*/

class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int cur = arr.front(), win = 0;
        for(int i = 1; i < arr.size(); ++i) {
            if(arr[i] > cur) {
                cur = arr[i];
                win = 0;
            }
            if(++win == k) break;
        }
        return cur;
    }
};
