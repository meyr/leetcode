/* Greedy point : 顏色一樣只保留neededTime最大的
 *
 * time  : O(N + N) = O(N)
 * space : O(1)
 */
class Solution {
public:
    int minCost(string colors, vector<int>& neededTime) {
        int remain{}, maxv{neededTime[0]};
        int total = accumulate(begin(neededTime), end(neededTime), 0);
        char prev = colors[0];
        colors.push_back('A');
        neededTime.push_back(0);
        for(int i = 1; i < colors.size(); ++i) {
            char& cur = colors[i];
            int time = neededTime[i];
            if(prev != cur) {       // 顏色不一樣 保留最大的
                remain += maxv;
                maxv = time;
            } else                  // 顏色一樣 繼續統計相同顏色的最大neededTime
                maxv = max(maxv, time);
            prev = cur;
        }
        return total - remain;
    }
};
