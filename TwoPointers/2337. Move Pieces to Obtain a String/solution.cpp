/*
 * 參考解答
 *
 * 因為跳過了'_' 所以會有幾種狀況
 * 1. i == start.size() --> 判斷 j == target.size()
 * 2. start[i] == 'L' target[j] == 'R' 一定是錯誤
 * 3. start[i] == 'L' target[j] == 'L' i必須 >= j
 * 4. start[i] == 'R' target[j] == 'L' 一定是錯誤
 * 5. start[i] == 'R' target[j] == 'R' i必須 <= j
 *
 * time  : O(N + N)  = O(N) 兩個string都會走過一次
 * sapce : O(1)
 */
class Solution {
public:
    bool canChange(string start, string target) {
        int n = start.size();
        int i{}, j{};
        while(i < n && j < n) {
            while(i < n && start[i] == '_') ++i; // 找出第一個非'_'的char
            while(j < n && target[j] == '_') ++j;
            if(i == n or j == n) return i == n and j == n;  // 如果到底了 則判斷是否兩個字串都看過了
            else if(start[i] != target[j]) return false;    // 不相同一定是錯誤
            else if(start[i] == 'L' && j > i) return false; // 如果是'L' 則i >= j i可以向左移動去滿足j 否則無法達到
            else if(start[i] == 'R' && i > j) return false; // 如果是'R' 則j >= i i可以向右移動去滿足j 否則無法達到
            i++, j++;
        }
        while(i < n && start[i] == '_') ++i;  // 跳過尾巴的'_'
        while(j < n && target[j] == '_') ++j; //
        return i == n and j == n;
    }
};
