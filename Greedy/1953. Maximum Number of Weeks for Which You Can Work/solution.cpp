/*
 *  重點在於最多的那個project可否全部排入
 *  
 *  如果mx <= rest 表示可以全部排入 那表示所有的project都可以排入
 *  否則就是 mx和rest交叉排列 2 * rest 最後再放入一個mx --> 2 * rest + 1
 *
 */
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        int mx = *max_element(begin(milestones), end(milestones));
        long long sum = accumulate(begin(milestones), end(milestones), 0LL);
        long long rest = sum - mx;
        if(mx <= rest) return sum;
        else return rest * 2 + 1;
    }
};
