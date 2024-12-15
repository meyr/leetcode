/*  目的是使平均通過率最高
 *  所以extra student加入之後可以有最大的成長率
 *  使用priority_queue自定義cmp function比較
 *
 *  time  : O(NlogN + KlogN + N) = O((N+k)logN)
 *  space : O(N)
 */
class Solution {
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        auto diff = [](vector<int>& a) {
            return ((double)a[0] + 1)/(a[1] + 1) - (double)a[0]/a[1];
        };
        auto cmp = [&](vector<int>& a, vector<int>& b){
            return diff(a) < diff(b);
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq(cmp);
        for(auto& c : classes) pq.push(c); // O(N)
        while(extraStudents--) { // O(KlogN)
            vector<int> val = pq.top(); pq.pop();
            val[0]++;
            val[1]++;
            pq.push(val);
        }
        int sz = classes.size();
        double ans;
        while(!pq.empty()) { // O(N)
            vector<int> val = pq.top(); pq.pop();
            ans += val[0] * 1.0 / val[1];
        }
        return ans / sz;
    }
};
/*
    (3/4 + 3/5 + 2/2) / 3

    3/12 + 3/15 + 2/6

    a/b --> (a+1)/(b+1)
    1/2 --> 0.5 --> 2/3 --> 0.666 -> 0.75 -> 0.8
    3/5 --> 0.6 --> 4/6 --> 0.666 -> 0.71 -> 0.75
    2/2--> 1 --> 3/3 --> 1 -> 1

    a+1/b+1 - a/b
*/
