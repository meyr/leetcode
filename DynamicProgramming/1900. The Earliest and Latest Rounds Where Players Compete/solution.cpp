/*  ref to : https://leetcode.com/problems/the-earliest-and-latest-rounds-where-players-compete/solutions/1268539/recursion-memo-and-optimized-recursion-b-319s/
 *  模擬比賽的過程 先找出兩個選手 然後第一個晉級或是第二的晉級 
 *  直到firstplayer和secondplayer碰到 此比賽就結束
 *
 *  這邊的重點是一個round的結束是 i>=j 也就是有ij是中間選手或是i>j 就會進行下一個round
 *  當firstPlayer和secondPlayer碰在一起就收集此次比賽的結果
 *
 *  當i == firstPlayer or i == secondPlayer就一定會晉級，同理j也是。
 *
 *  time  = O(2^N)  因為每個player都有兩種可能
 *  space = O(2^N)
 */
class Solution {
    int min_r = INT_MAX, max_r = INT_MIN;
    void dfs(int mask, int round, int i, int j, int first, int second) {
        if(i >= j) //已經抵達此round的mid player
            dfs(mask, round + 1, 0, 27, first, second); // 重新下一round
        else if((mask & (1 << i)) == 0) // i選手已經比過
            dfs(mask, round, i + 1, j, first, second);
        else if((mask & (1 << j)) == 0) // j選手已經比過
            dfs(mask, round, i, j - 1, first, second);
        else if(i == first and j == second) { // 剛好是first 和 second比，此round結束
            min_r = min(min_r, round);
            max_r = max(max_r, round);
        } else {
            if(i != first and i != second) // i選手落敗，j選手晉級
                dfs(mask ^ (1 << i), round, i + 1, j - 1, first, second);
            if(j != first and j != second) // i選手晉級，j選手落敗
                dfs(mask ^ (1 << j), round, i + 1, j - 1, first, second);
        }
    }
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        dfs((1 << n) - 1, 1, 0, 27, firstPlayer - 1, secondPlayer - 1);
        return {min_r, max_r};
    }
};
/*  memorization : 如果單純對mask, i, j來紀錄只有適度的提升。
 *  答案的結果和firstPlayer, secondPlayer前後的player數有關。
 *  也就是在firstPlayer之前，secondPlayer和firstPlayer中間，和secondPlayer之後的player數有關
 *
 *  time  : O(N^3) 因為l, m, r範圍為0~N-1
 *  space : O(N^3)
 */
 class Solution {
    int min_r = INT_MAX, max_r = INT_MIN;
    //bool visited[27][27][27] = {};
    void dfs(int mask, int round, int i, int j, int first, int second, int l, int m, int r) {
        if(i >= j) //已經抵達此round的mid player
            dfs(mask, round + 1, 0, 27, first, second, l, m, r); // 重新下一round
        else if((mask & (1 << i)) == 0) // i選手已經比過
            dfs(mask, round, i + 1, j, first, second, l, m, r);
        else if((mask & (1 << j)) == 0) // j選手已經比過
            dfs(mask, round, i, j - 1, first, second, l, m, r);
        else if(i == first and j == second) { // 剛好是first 和 second比，此round結束
            min_r = min(min_r, round);
            max_r = max(max_r, round);
        } else {
        //} else if(!visited[l][m][r]){ // i選手晉級或是j選手晉級
            //visited[l][m][r] = true;
            if(i != first and i != second) // i選手落敗，j選手晉級。根據i所在位置跟新l, m, r
                dfs(mask ^ (1 << i), round, i + 1, j - 1, first, second,
                 l - (i < first), m - (i > first && i < second), r - (i > second)); // 重新計算l, m, r
            if(j != first and j != second) // i選手晉級，j選手落敗。根據j所在的位置跟新l, m, r
                dfs(mask ^ (1 << j), round, i + 1, j - 1, first, second,
                l - (j < first), m - (j > first && j < second), r - (j > second));
        }
    }
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        dfs((1 << n) - 1, 1, 0, 27, firstPlayer - 1, secondPlayer - 1
            , firstPlayer - 1, secondPlayer - firstPlayer - 1, n - secondPlayer);
        return {min_r, max_r};
    }
};
