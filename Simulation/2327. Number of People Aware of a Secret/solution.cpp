/*  參考 : https://leetcode.com/problems/number-of-people-aware-of-a-secret/solutions/2229808/two-queues-or-rolling-array-by-votrubac-af68/
 *
 *  有時候求好心切 想要一次到位 反而解不出問題
 *  照著題議做 先寫出解答比較重要
 *  這題可以根據提議 使用兩個deque<int> 分別統計delay和forget
 *
 *  time  : O(N)
 *  space : O(D + F)
 */
class Solution {
public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        long long ans{}, share{};
        int mod = 1e9 + 7;
        deque<int> d{1}, f{1};  // day1 只有一個人知道秘密
        while(--n > 0) {
            if(d.size() >= delay) { // d.size() >= delay 表示有人delay時間已過 可以開始分享祕密
                share = (share + d.front()) % mod;
                d.pop_front();
            }
            if(f.size() >= forget) {    // f.size() >= forget 表示有人forget時間已到 需要從share內移除
                share = (share - f.front() + mod) % mod;    // 會出現這種情況嗎?
                f.pop_front();
            }
            d.push_back(share);                             // 可以分享的人繼續排入delay和forget的deque內
            f.push_back(share);
        }
        return accumulate(begin(f), end(f), 0LL) % mod;     // 全部知道秘密的人就是forget內所有的人
    }
};
