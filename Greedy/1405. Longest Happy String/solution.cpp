/*  ref : https://leetcode.com/problems/longest-happy-string/solutions/564277/c-java-a-b-c/
 *
 *  一開始是使用priority_queue來解 但是卡在一個地方 容易會把substring拼成三個一樣的char
 *  參考上面的解答
 *  什麼情況才可以使用 第二的char? 當第一個char數量大於等於第二個的時候 
 *  因為放回priority_queue他還是會第一個 就不會出現同時三個char的情況
 *
 */
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        priority_queue<pair<int, char>> pq;
        pq.push({a, 'a'}), pq.push({b, 'b'}), pq.push({c, 'c'});
        string ans{};
        while(!pq.empty()) {
            auto [cnt1, ch1] = pq.top(); pq.pop();
            auto [cnt2, ch2] = pq.top(); pq.pop();
            int used = min(2, cnt1);
            ans += string(used, ch1);
            if(cnt2 == 0) return ans;   // __important__ 第二個沒了就不用繼續
            int remain = cnt1 - used;
            if(remain >= cnt2) {        // __important__ 第一個剩下的還是比第二個多才可以接ch2 不然下一輪會變成ch2最大造成三個連續char 
                ans += string(1, ch2);
                cnt2--;
            }
            pq.push({remain, ch1}), pq.push({cnt2, ch2});
        }
        return ans;
    }
};
/*  ref : https://leetcode.com/problems/longest-happy-string/solutions/564277/c-java-a-b-c/
 *  
 *  這邊個解答是利用function來達到priority_queue的功效
 */
class Solution {
public:
    string longestDiverseString(int a, int b, int c, char aa = 'a', char bb = 'b', char cc = 'c') {
        if (a < b)                                                  //  經過這四行後 a >= b >= c 所以取到的a和aa 一定是最多的那個
            return longestDiverseString(b, a, c, bb, aa, cc);       //
        if (b < c)                                                  //
            return longestDiverseString(a, c, b, aa, cc, bb);       //
        if (b == 0)                                                     
            return string(min(2, a), aa);                           // b == 0 只能使用a 
        auto use_a = min(2, a), use_b = a - use_a >= b ? 1 : 0;
        return string(use_a, aa) +  string(use_b, bb) +
            longestDiverseString(a - use_a, b - use_b, c, aa, bb, cc);
    }
};
