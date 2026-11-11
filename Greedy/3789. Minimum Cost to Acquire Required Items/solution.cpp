/*
 *      一開始使用dynamic programming的方法解 結果錯了
 *      因為這邊要求可以買超過need1, 或是need2只要cost最低就可以了
 */
class Solution {
    int cost1, cost2, costBoth;
    int helper(int need1, int need2) {
        if(need1 == 0 && need2 == 0) return 0;
        else if(need1 == 0) return need2 * cost2;
        else if(need2 == 0) return need1 * cost1;
        else {
            return min({
                helper(need1 - 1, need2) + cost1,
                helper(need1, need2 - 1) + cost2,
                helper(need1 - 1, need2 - 1) + costBoth
            });
        }
    }
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        this->cost1 = cost1;
        this->cost2 = cost2;
        this->costBoth = costBoth;
        return helper(need1, need2);
    }
};
/*
 *      後來想一想應該是Greedy問題
 *      因為如果costBoth <= cost1 + cost2 那就是同時買進兩個item
 *                                        剩下的就是單獨買進 或是同時買進兩個方法 看哪一個比較省
 *
 *          如果costBoth  > cost1 + cost2 那使用costBoth就沒意義分開買進就好
 *
 *      time  : O(1)
 *      space : O(1)
 */
class Solution {
public:
    long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
        if(need2 > need1) {     // need1 >= need2
            swap(need1, need2);
            swap(cost1, cost2);
        }
        long long ans{};
        if(cost1 + cost2 >= costBoth) {
            ans = (long long)need2 * costBoth;
            long long diff = need1 - need2;
            return ans + min(diff * cost1, diff * costBoth);
        } else
            return (long long)cost1 * need1 + (long long)cost2 * need2;
    }
};
