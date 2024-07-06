/*
 *  根據下面的推算 因為要取mode所以最好是0,1,2... 所以把time先減一
 *  time  : O(1)
 *  space : O(1)
 */
class Solution {
public:
    int passThePillow(int n, int time) {
        time--;
        time %= (2 * n - 2);
        if(time <= n - 2) return time + 2;
        else {
            time -= n - 1;
            return n - 1 - time;
        }
    }
};

/*
    1, 2, 3, 4,    n = 4
       0  1  2
    5  4  3   
*/
