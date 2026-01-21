/*
Input | Answer | Input | Answer
-------------------------------
2           -1      10
3            1      11       1
                    -
5            4     101     100
                     -
7            3     111      11
                   -
11           9    1011    1001
                    -
13          12    1101    1100
                     -
31          15   11111    1111
                 -
 *  觀察input 和 answer的結果會發現 只要移除從右邊看過來連續1的最左邊
 *  time  : O(N*32) = O(N)
 *  space : O(N)
 */
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> rtn;
        for(auto& n : nums) {
            if(n % 2 == 0) rtn.push_back(-1);
            else {
                bitset<32> b(n);
                int i = 0;
                while(i < 32 && b.test(i)) i++;
                b[i - 1] = 0;
                rtn.push_back(static_cast<int>(b.to_ulong()));
            }
        }
        return rtn;
    }
};
