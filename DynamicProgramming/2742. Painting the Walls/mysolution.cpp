/*
 *  __NOT AC solution__
 *
 *  一開始我使用Greedy的想法 先依據cost排序 然後依次取出
 *  會遇到一種情況 因為是依cost排序 取[20,3] 會比取[10, 1]+[10,1]好
 *
 *  [10, 1][10, 1] ...[20, 3]
 *
 */

class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        vector<vector<int>> ct;
        for(int i = 0; i < cost.size(); ++i)
            ct.push_back({cost[i], time[i]});
        sort(begin(ct), end(ct), [](auto& a, auto& b){
            if(a[0] < b[0]) return true;
            else if(a[0] == b[0]) return a[1] > b[1];
            else return false;
        });
        int min_cost{}, take_times{};
        for(int i = 0, rem = ct.size(); i < ct.size(); ++i) {
            min_cost += ct[i][0];
            take_times += ct[i][1];
            if(take_times >= ct.size() - i - 1) break;
        }
        return min_cost;
    }
};
