/*      參考leetcode官方解答
 *
 *      每一次operation就是選一個subarray然後進行排序 --> 所以如果可以選擇全部就可以一次排序
 *      不過題目提到不能選entire string 那退而求其次 次長subarray就是 s.size() - 1
 *
 *      case 1 : 已經排列好了 所以是 ans = 0
 *      case 2 : 如果第一個char是最小 或是 最後一個char是最大 那我就選擇s.size() - 1的subarray排序 所以是 ans = 1
 *      case 3 : 最大char或是最小char在中間 找出最小的最後一個index前面全部排序
 *
 *                  xxxx'a'xx'z'xxx  遇到最小 就把最小char開始往前全部排續 --> 這樣就回歸到 case2
 *                  |    |
 *
 *                            |   |   同理如果遇到最大char 就是從此char往後全部排序 --> 這樣就回歸到case2
 *
 *      case 4 : 如果這種情況 'z'xxxxxx'a'
 *                             |      |      ---> xxxxxx'z''a'
 *                                                 |        |     ---> x'a'xxxxx'z'
 *                                                                     |       |        ans = 3
 *
 */
class Solution {
public:
    int minOperations(string s) {
        char mx = 'a', mn = 'z';
        int n = s.length();
        for (int i = 0; i < n; i++) {
            mx = max(mx, s[i]);
            mn = min(mn, s[i]);
        }
        if (ranges::is_sorted(s)) {             // case 1
            return 0;
        }
        if (n == 2) {                           // 因為不是已經排序過 也是sz = 2 表示不能排序不能進行任何operation所以是-1
            return -1;
        }
        if (s[0] == mn || s[n - 1] == mx) {     // case 2
            return 1;
        }
        for (int i = 1; i < n - 1; i++) {       // case 3
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }
        return 3;                               // case 4
    }
};
