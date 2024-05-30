/*
 *  很直覺的照著題目的意思做 得到不好的Time complexity
 *  要注意的是 i < j <= k, j和k可以相等
 *
 *
 *  time  : O(N + N^3) = O(N^3)
 *  space : O(1) 
 */
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int sz = arr.size();
        for(int i = 1; i < sz; ++i)
            arr[i] ^= arr[i - 1];
        int ans{};
        for(int i = 0; i < sz; ++i) {
            for(int j = i + 1; j < sz; ++j) {
                for(int k = j; k < sz; ++k) {
                    if((arr[j - 1] ^ (i == 0 ? 0 : arr[i - 1])) == 
                       (arr[k] ^ arr[j - 1])) {
                        ans++;
                    }
                }
            }
        }
        return ans;
    }
};
