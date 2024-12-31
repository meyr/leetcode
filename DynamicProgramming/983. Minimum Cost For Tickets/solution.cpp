/*
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    unordered_set<int> td;
    vector<int> costs;
    int helper(int day) {
        if(day < 0) return 0;
        else if(~mem[day]) return mem[day];
        else if(!td.count(day)) return mem[day] = helper(day - 1);
        return mem[day] = min({ // 今天買入ticket 一定是用完再買入下一張票
            day - 1 >= 0  ? helper(day - 1) + costs[0] : costs[0],
            day - 7 >= 0  ? helper(day - 7) + costs[1] : costs[1],
            day - 30 >= 0 ? helper(day - 30) + costs[2] : costs[2]
        });
    }
    vector<int> mem;
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        for(auto& d : days) td.insert(d);
        this->costs = costs;
        mem.resize(366, -1);
        mem[0] = 0;
        return helper(365);
    } 
};
/*  2024/12/31 daily challenge
 *
 *  和上面的想法差不多
 */
class Solution {
    int helper(int d, unordered_set<int>& sdays, vector<int>& costs) {
        if(d > 365) return 0;
        else if(~mem[d]) return mem[d];
        else if(sdays.count(d)) {
            return mem[d] = min({
                        costs[0] + helper(d + 1, sdays, costs),
                        costs[1] + helper(d + 7, sdays, costs),
                        costs[2] + helper(d + 30, sdays, costs)});
        } else return mem[d] = helper(d + 1, sdays, costs);
    }
    vector<int> mem;
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        unordered_set<int> sdays(begin(days), end(days));
        mem.resize(366, -1);
        return helper(1, sdays, costs);
    }
};
