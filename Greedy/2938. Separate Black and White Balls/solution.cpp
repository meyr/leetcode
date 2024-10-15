/*  我的解答使用two pointer分別找出需要swap的位置
 *
 *  time  : O(N)
 *  space : O(1)
 */
class Solution {
public:
    long long minimumSteps(string s) {
        int i = s.size() - 1;
        while(i >= 0 && s[i] == '1') --i; //  先找出第一個0的位置
        int j = i - 1;                    // j從第一個0之前開始找
        long long ans{};
        while(j >= 0) {
            while(i >= 0 && s[i] == '1') --i;  
            while(j >= 0 && s[j] == '0') --j;
            if(j >= 0) { // 有找到s[j] == '1'
                ans += i - j;
                swap(s[i], s[j]);
            }
        }
        return ans;
    }
};
/*
            j i              
    0,1,0,0,1,0,1
    0,1,0,0,0,1,1
      j     i
   j      i
*/



/*  參考 : https://leetcode.com/problems/separate-black-and-white-balls/solutions/4304301/two-pointers-vs-counter/
 *
 *  0,1,0,1,0,0   cnt : 計算有幾個'1', 當遇到'0'表示之前遇到的'1'一起往前移動
 *    *           cnt = 1, ans = 0
 *      *         cnt = 1, ans = 1  --> 0,0,1,1,0,0  一個'1'同時往前 ans += cnt 
 *        *       cnt = 2, ans = 1
 *          *     cnt = 2, ans = 3  --> 0,0,0,1,1,0  兩個'1'同時往前 ans += cnt
 *            *   cnt = 2, ans = 5  --> 0,0,0,0,1,1  兩個'1'同時往前 ans += cnt
 *
 *  time  : O(N)
 *  space : O(1)
 */   
class Solution {
public:
    long long minimumSteps(string s) {
        long long ans{};
        for(int i = 0, cnt = 0; i < s.size(); ++i) {
            if(s[i] == '1') cnt++;
            else ans += cnt;
        }
        return ans;
    }
};
