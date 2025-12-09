/*
 *  要找出每個index開始最長match的prefix --> 使用z-algorithm
 *  
 *  ref : https://www.geeksforgeeks.org/dsa/z-algorithm-linear-time-pattern-searching-algorithm/
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    vector<int> z_algorithm(string& s) {
        int sz = s.size(), left = 0, right = 0;
        vector<int> z(sz);
        for(int i = 1; i < sz; ++i) {
            if(i <= right) {                        // i 在 z-box內
                int k = i - left;
                z[i] = min(z[k], right - i + 1);
            }
            while(i + z[i] < sz && s[i + z[i]] == s[z[i]]) z[i]++;
            if(i + z[i] - 1 > right) {
                left = i;
                right = i + z[i] - 1;
            }
        }
        return z;
    }
public:
    long long sumScores(string s) {
        vector<int> z = z_algorithm(s);
        return accumulate(begin(z), end(z), 0LL) + s.size(); // 因為z[0] == 0, 但是題目來看是完全match所以加上s.size();
    }
};
