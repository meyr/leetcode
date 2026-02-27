/*  參考AI的解答
 *  
 *  這題是【狀態壓縮】的題目，也就是說目前的狀態，跳到下一個狀態。
 *  目前的狀態是有幾個0(m), 經過一次操作(k 個index的flip之後)，跳到下一個狀態(m')有幾個0
 *
 *  假設選中c個0, 那就是選中k-c個1
 *  m' = m - c + (k - c)
 *  m' = m + k - 2c       因為2c一定為偶數，所以m+k和m'一定是相同的奇偶特性。
 *
 *  c 的範圍如何? 因為我們不可能無限指的選取
 *  
 *  max_c 最多能選到幾個 0？
 *  限制一： 你選到的 0，不能超過字串中目前擁有的 0 (curr)。
 *  限制二： 你選到的 0，不能超過視窗的大小 (k)。
 *  
 *  max_c = min(k, curr);
 *
 *  min_c 最少要選到幾個 0？
 *  假設視窗大小為k，如果你只選了c個 0，剩下的k - c個位置必須是1。
 *  如果你手上的 1 總數不夠，這個c就是無效的。
 *  我們擁有的 1 的總數是 n - curr。
 *  我們選的 1 的數量是 k - c。
 *  條件是：選擇的 1 不能超過擁有的 1 --> k - c <= n - curr。
 *          c >= k - (n - curr)。
 *
 *  當然，c絕對不能小於 0。
 *  min_c = max(0, k - (n - curr));
 */
 class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size();
        int initial_zeros = 0;
        for (char c : s) if (c == '0') initial_zeros++;

        // dist[i] 代表變成 i 個 0 需要幾次操作
        // 初始化為 -1 代表還沒走過這個狀態
        vector<int> dist(n + 1, -1);
        queue<int> q;

        q.push(initial_zeros);
        dist[initial_zeros] = 0;    // 從目前有幾個零開始

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            // 沒有半個0，代表全變成 1 了，回傳答案
            if (curr == 0) return dist[curr];

            // 嘗試所有可能的翻轉情況
            int min_c = max(0, k - (n - curr)); // curr : 目前0的數量，n - curr : 目前1的數量, k - (n - curr)
            int max_c = min(k, curr);

            for (int c = min_c; c <= max_c; ++c) {
                int next_zeros = curr - c + (k - c); // 翻轉後的 0 數量

                // 如果這個狀態還沒走過，就把它加入隊列
                if (dist[next_zeros] == -1) {
                    dist[next_zeros] = dist[curr] + 1;
                    q.push(next_zeros);
                }
            }
        }
        return -1; // 無法達成
    }
};
/*  結果是TLE
 *  因為while() + for() 的time complexity為O(NK)
 *  必須優化for loop
 *  檢查過的state不需要重複檢查 因為m' = m + k - 2c 所以只需要檢查相同奇偶屬性
 */
class Solution {
public:
    int minOperations(string s, int k) {
        int n = s.size();
        int initial_zeros = 0;
        for (char c : s) if (c == '0') initial_zeros++;

        // 1. 初始化：將所有可能的狀態 (0 到 n 個 '0') 分成兩組：奇數組和偶數組
        // 這樣做是為了符合我們之前討論的「奇偶性不變」原則
        set<int> unvisited[2];
        for (int i = 0; i <= n; ++i) {
            if (i != initial_zeros) unvisited[i % 2].insert(i);
        }

        // 2. BFS 準備
        queue<int> q;
        q.push(initial_zeros);
        vector<int> dist(n + 1, -1);
        dist[initial_zeros] = 0;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            if (curr == 0) return dist[0];

            // 3. 計算合法狀態範圍 [L, R]
            int min_c = max(0, k - (n - curr));
            int max_c = min(k, curr);
            int L = curr + k - 2 * max_c; // 因為m' = m + k - 2c  所以最小值是減最多的
            int R = curr + k - 2 * min_c; //                          最大值是減最少的

            // 4. 關鍵優化：只在未訪問的節點中找範圍內的點
            auto& targetSet = unvisited[L % 2];
            auto it = targetSet.lower_bound(L);

            // 只要找到符合條件的，就把它「抓」出來並標記，確保它不再被重複掃描
            while (it != targetSet.end() && *it <= R) {
                int next_m = *it;
                dist[next_m] = dist[curr] + 1;
                q.push(next_m);
                
                // 執行 erase 後，it 會失效，所以要用 iterator 遞增技巧
                targetSet.erase(it++); 
            }
        }
        return -1;
    }
};
