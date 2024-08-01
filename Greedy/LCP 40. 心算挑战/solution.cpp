/*
 *  試了很多次才AC
 *
 *  先貪心的把最大的都收集起來
 *  如果是even就返回
 *  如果是odd  --> 收集來的cards中有奇數個奇數(1, 3, 5, ...), 必須有偶數個奇數(0, 2, 4, 6, ...)
 *  
 *  所以 開始往下看 如果是遇到偶數 --> 丟掉最小的奇數
 *                  如果是遇到奇術 --> 丟掉最小的偶數
 *
 *  time  : O(NlogN + N) = O(NlogN)
 *  space : O(logN)
 */
class Solution {
public:
    int maxmiumScore(vector<int>& cards, const int cnt) {
        int sz = cards.size();
        int ans{}, total{}, lastEven{}, lastOdd{};
        sort(begin(cards), end(cards)); //O(NlogN) 因為cards[i]為1~1000 所以可以使用bucket sort節省時間
        for(int i = sz - 1; i >= sz - cnt; --i) { 
            total += cards[i];
            if(cards[i] & 1) lastOdd = cards[i];
            else lastEven = cards[i];
        }
        if(!(total & 1)) return total;
        for(int i = sz - cnt - 1; i >= 0; --i) {
            if(cards[i] & 1) {// odd
                if(lastEven != 0) ans = max(ans, total - lastEven + cards[i]);
            } else { //even
                if(lastOdd != 0) ans = max(ans, total - lastOdd + cards[i]);
            }
        }
        return ans;
    }
};
/*
    9, 5, 9, 1, 6, 10, 3, 4, 5, 1
    1, 1, 3, 4, 5, 5, 6, 9, 9, 10
                         *
    odd  :  9
    even : 10

*/
