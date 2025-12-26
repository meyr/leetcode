/*
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    int bestClosingTime(string customers) {
        int sz = customers.size();
        int n_cnt = count_if(begin(customers), end(customers), [](auto& c){
            return c == 'N';
        });
        int ans{sz}, count{n_cnt}, y_cnt{};
        for(int i = sz - 1; i >= 0; --i) {
            y_cnt += customers[i] == 'Y';
            n_cnt -= customers[i] == 'N';
            if(y_cnt + n_cnt <= count) {
                ans = i;
                count = y_cnt + n_cnt;
            }
        }
        return ans;
    }
};
/*
    Y, Y, N, Y
   |             idx = 0,   | Y, Y, N, Y -->3
      |          idx = 1,   Y | Y, N, Y  -->2 
         |       idx = 2,   Y, Y, | N, Y -->1           <-- small penalty
            |    idx = 3,   Y, Y, N, | Y -->1+1=2
               | idx = 4,   Y, Y, N, Y | -->1
*/ 
