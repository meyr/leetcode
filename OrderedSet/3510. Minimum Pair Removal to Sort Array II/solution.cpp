/* ref : https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/solutions/6621224/short-and-clean-c-code-only-set-and-vect-unvj/
 *
 * 1. 因為要模擬題目的processing 勢必要在vector中移除element, 最好的移除方法是使用double linked list
 *    不然在vector移除element是O(N)
 *    但是在double linked list確不好找尋element需要O(N)
 *    所以這邊使用vector另外使用兩個vector分別儲存index i的前後index
 *    ```cpp
 *    vector<int> nums;
 *    vector<int> prev(nums.size()), next(nums.size());
 *    for(int i = 0; i < nums.size(); ++i) {
 *      prev[i] = i - 1;
 *      next[i] = i + 1;
 *    }
 *    ```
 *    當移除的時候 只要連結前後的element
 *    ```cpp
 *    // remove element i
 *    next[i - 1] = i + 1;
 *    prev[i + 1] = i - 1;
 *    ```
 *    但是無法增加element 剛好這個題目不需要增加element
 *
 * 2. 使用set<pair<long long, int>> 來記錄每個pair的sum和index, 使用set才可以找出每個pair sum的最小值
 *    但是一個element被移除 必需更新前後pair sum
 *    例如: [5, 2, 3, 1]  --> {4, 2}, {5, 1}, {7, 0}
 *    當 [2, 3] 被合併之後 就是 [5, 5, 1] --> {6, 1}, {10, 0}
 *    就是[2, 3] 這組會被移除 同時 [5, 2] 會變成 [5, 5], 另外[3, 1] 會變成[5, 1]
 *
 * 3. 使用cnt來記錄還有多少次更新 因為我們要達到non-decreasing
 *    所以 cnt += nums[i] > nums[i + 1]
 *    同時只要更新一個element 則 還要再check一次前後關係 update cnt
 */
using ll = long long;

class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        vector<ll> a(n);                                // 使用vector<ll>來記錄 因為兩個數相加可能超過int
        for (int i = 0; i < n; i++) a[i] = nums[i];

        // maintain adjacent pairs {sum, index}
        set<pair<ll, int>> s;                           // 使用set<pair<ll, int>>來記錄pair sum和index

        // double-linked list
        vector<int> nxt(n);
        vector<int> pre(n);
        for (int i = 0; i < n; i++) nxt[i] = i + 1;
        for (int i = 0; i < n; i++) pre[i] = i - 1;

        // insert all pairs into set
        int cnt = 0;
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) cnt++;                 // 不是non-decreasing 所以cnt + 1 目前最少需要操作的次數
            s.insert({a[i] + a[i + 1], i});
        }

        // simulate the process
        int ans = 0;
        while (cnt > 0) {                               // 四個element的關係
            int i = s.begin()->second;                  //                          s.begin() : pair sum最少的那一組
            int j = nxt[i];                             //  _p_,  _i_,  _j_,  _q_
            int p = pre[i];                             //
            int q = nxt[j];                             //

            // pair {i, j}                              // 因應兩個數merge起來後 cnt可能的變化
            if (a[i] > a[j]) cnt--;                     // 原本的狀況
            if (p >= 0) {                               // 有p的狀況
                // pair {p, i}
                if (a[p] > a[i] && a[p] <= a[i] + a[j]) {   // 原本是 a[p] > a[i] , merge之後 a[p] <= a[i] + a[j] 符合條件, 所以把原先a[p] > a[i]情況檢掉
                    cnt--;
                }
                else if (a[p] <= a[i] && a[p] > a[i] + a[j]) {  // 原本是 [p] <= a[i] 已經符合條件, 但是merge之後 a[p] > a[i] + a[j] 變成不符合, 所以cnt++
                    cnt++;
                }
            }
            if (q < n) {                                        // 這邊使用的是只有四種情況
                // pair {j, q}                                  //
                if (a[q] >= a[j] && a[q] < a[i] + a[j]) {       //    origin   merge
                    cnt++;                                      //     符合    符合
                }                                               //    不符合   符合     ---+--> 只有這兩種情況才需要更新
                else if (a[q] < a[j] && a[q] >= a[i] + a[j]) {  //     符合    不符合   --/
                    cnt--;                                      //    不符合   不符合
                }
            }                                                   //  這樣的判斷有點複雜 我會偏向先把之前的狀況檢掉 再把之後的狀況加回去

            // remove outdated pairs & add new pairs            //  更新 pair sum
            s.erase(s.begin());                                 //   p, i, j, q  --> p, i + j, q
            if (p >= 0) {                                       //   ----
                s.erase({a[p] + a[i], p});                      //                  ----------
                s.insert({a[p] + a[i] + a[j], p});              //
            }                                                   //
            if (q < n) {                                        //   p, i, j, q --> p, i + j, q
                s.erase({a[j] + a[q], j});                      //         ----
                s.insert({a[i] + a[j] + a[q], i});              //                     --------
                pre[q] = i;                                     // 更新 next, prev 和 a
            }                                                   //   p, i+j, j, q
            nxt[i] = q;                                         //       -------> next[i] = q
            a[i] = a[i] + a[j];                                 //       <------- prev[q] = i
            ans++;                                              //
        }

        return ans;
    }
};
/*
 *  理解之後 根據自己的想法 重新寫過
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int sz = nums.size(), ans{}, cnt{};
        vector<long long> llnums(begin(nums), end(nums));   // O(N)
        vector<int> prev(sz, sz - 2), next(sz, sz);         // O(N)
        set<pair<long long, int>> s;
        for(int i = 0; i < sz - 1; ++i) {                   // O(N)
            prev[i] = i - 1;
            next[i] = i + 1;
            cnt += llnums[i] > llnums[i + 1];
            s.insert({llnums[i] + llnums[i + 1], i});
        }
        while(cnt) { //O(NlogN)                   // p, i, j, q  --> p, i + j, j , q
            int i = s.begin()->second;
            int j = next[i];
            int p = prev[i];
            int q = next[j];

            // update cnt
            cnt -= llnums[i] > llnums[j];
            cnt -= q < sz ? llnums[j] > llnums[q] : 0;
            cnt -= p >= 0 ? llnums[p] > llnums[i] : 0;
            cnt += p >= 0 ? llnums[p] > llnums[i] + llnums[j] : 0;
            cnt += q < sz ? llnums[i] + llnums[j] > llnums[q] : 0;

            // update pair sum                            p, i, j, q -->  p, i + j, q
            s.erase({llnums[i] + llnums[j], i});
            if(p >= 0) {
                s.erase({llnums[p] + llnums[i], p});
                s.insert({llnums[p] + llnums[i] + llnums[j], p});
            }
            if(q < sz) {
                s.erase({llnums[j] + llnums[q], j});
                s.insert({llnums[i] + llnums[j] + llnums[q], i});
            }

            // update next, prev, llnums            p, i, j, q --> p, i+j, j, q
            llnums[i] += llnums[j];             //                     ------->
            next[i] = q;                        //                     <-------
            if(q < sz) prev[q] = i;

            ans++;
        }

        return ans;
    }
};
