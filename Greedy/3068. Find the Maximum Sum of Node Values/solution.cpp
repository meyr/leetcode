/*
 *  參考解答
 *  https://leetcode.com/problems/find-the-maximum-sum-of-node-values/solutions/4811460/greedy-sacrifice/
 *
 *  這邊的重點是xor 也就是說不管你怎麼選一定會有__偶數__個node被你改變
 *  而且是任意偶數個node，所以我們先找出n^k > n 的node
 *  如果 這樣的node為__基數__那就是犧牲最小的那一個 min(s, abs(n - (n^k)))
 *
 */
class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        long long sum{}, cnt{}, sacrifice = INT_MAX;
        for(long long n : nums) {
            sum += max(n ^ k, n);
            cnt += (n ^ k) > n;
            sacrifice = min(sacrifice, abs(n - (n ^ k)));
        }
        return sum - (cnt % 2 ? sacrifice : 0);
    }
};
/*  2025/05/24 一樣沒解答出來 參考
 *  https://leetcode.cn/problems/find-the-maximum-sum-of-node-values/solutions/3674731/zui-da-jie-dian-jie-zhi-zhi-he-by-leetco-7fmo/
 *  因為xor的關係，我可以對任兩個點進行xor即使這兩個點不是在相同edge上面
 *  Greedy point : 所以我可以對所有n^k > n的node進行運算這樣才可以達到最大sum
 *  如果n^k>n 的node數為偶數，則全部都可以轉化
 *                      奇數，則有兩種情況, case 1 : 犧牲轉換後差值最小的那一個，也就是abs(n - (n^k)) 最小的那個
 *                                          case 2 : 轉化多出來的那個點，搭配一個 n^k <= n 且轉化後損失最小的node
 *                                                                       轉化後損失最小--> abs(n^k - n) 最小
 */
 class Solution {
public:
    long long maximumValueSum(vector<int>& nums, int k, vector<vector<int>>& edges) {
        long long sum{};
        int cnt{}, minVal = INT_MAX;
        for(auto& n : nums) {
            cnt += (n ^ k) > n;
            sum += max(n, n ^ k);
            minVal = min(minVal, abs(n - (n ^ k))); // 變化最小的那一個，
                                                    // 因為cnt為奇數勢必要犧牲一個
                                                    // case1, 選一個n^k > n中最小的一個不變化
                                                    // case2, 選一個n^k > n和n^k <= k一起變化
                                                    // 上面兩個case都是把minVal減掉就可以達到
        }
        return sum - (cnt % 2 ? minVal : 0);
    }
};
