/*  參考解答
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    int candy(vector<int>& ratings) {
        int sz = ratings.size();
        vector<int> candy(sz, 1);
        for(int i = 1; i < sz; ++i)             // 先比較左邊
            if(ratings[i] > ratings[i - 1])
                candy[i] = candy[i - 1] + 1;    // rating大，就是要比左邊還多一個
        for(int i = sz - 2; i >= 0; --i) {      // 再比較右邊
            if(ratings[i] > ratings[i + 1])
                candy[i] = max(candy[i], candy[i + 1] + 1); // rating比較大，1. 本來candy[i]就比candy[i + 1]還多，
                                                            //               2. 取candy[i + 1] + 1                --> 這兩種情況取max 
        }
        return accumulate(begin(candy), end(candy), 0);
    }
};
