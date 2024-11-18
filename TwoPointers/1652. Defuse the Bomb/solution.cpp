/* 這題酸然是easy但是陷阱很多
 *
 *    5, 7, 1, 4    k = 3
 *    *  +  +  +      7+1+4  i + 1 % sz --> i + k % sz
 *    +  *-             1+4+5 = prev + 5 - 7
 *       +  *-            4+5+7 = prev + 7 - 1
 *          +  *-           5+7+1 = prev + 1 - 4
 *  
 *  
 *    2, 4, 9, 3     k = -2
 *    *     +  +     9+3
 *    +  *  -           3+2 = prev + 2 - 9
 *       +  *  -          2+4 = prev + 4 - 3 
 *    -     +  *            4+9 = prev + 9 - 2
 *
 *
 */
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int sz = code.size(), sum{};
        vector<int> rtn(sz);
        if(k == 0) return rtn;
        else if(k > 0) {
            for(int i = 1; i <= k; ++i) sum += code[i % sz];
            rtn[0] = sum;
            for(int i = 1; i < sz; ++i) {
                sum += code[(i + k) % sz] - code[i % sz];
                rtn[i] = sum;
            }
        } else {
            for(int i = (sz + k) % sz; i < sz; ++i) sum += code[i];
            rtn[0] = sum;
            for(int i = 1; i < sz; ++i) {
                sum += code[(i - 1 + sz) % sz] - code[((i + k - 1) % sz + sz) % sz];
                rtn[i] = sum;
            }
        }
        return rtn;
    }
};
/*
*/

/* 參考解答
 * 找出left和right之後就可以靠left++ 和++right來移動 不需要重算
 */
class Solution {
public:
    vector<int> decrypt(vector<int>& code, int k) {
        int sz = code.size();
        vector<int> ans(sz, 0);
        if(k == 0) return ans;
        int left  = k > 0 ? 1 : sz - -k;
        int right = k > 0 ? k : sz - 1;
        int sum = accumulate(begin(code) + left, begin(code) + right + 1, 0);
        for(int i = 0; i < sz; ++i) {
            ans[i] = sum;
            sum += code[++right % sz] - code[left++ % sz];
        }
        return ans;
    }
};
