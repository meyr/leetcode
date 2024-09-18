/*
 *  知道是要用sort但是怎麼寫都不對
 *  看了解答 int a, int b 要怎麼排列? 是要根據to_string(a) + to_string(b) 或是 to_string(b) + to_string(a) 哪一個比較大
 *
 *  time  : O(NlogN)
 *  space : O(logN)
 */
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        string res;
        sort(begin(nums), end(nums), [](int a, int b){ // __這邊判斷的條件是重點__
            return to_string(a) + to_string(b) > to_string(b) + to_string(a);
        });
        for(auto& n : nums)
            res += to_string(n);
        return res[0] == '0' ? "0" : res;
    }
};
