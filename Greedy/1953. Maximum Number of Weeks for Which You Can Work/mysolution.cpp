/*
 *  這個想法是錯誤的
 *  例如
 *  0, 1, 0, 1, 0, 1, 0, 2, 0, 2 如果project 2還有1個 可以往2前面一個任意位置插入
 *
 *  0, 1, _2_, 0, 1, 0, 1, 0, 2, 0, 2
 *
 */
class Solution {
public:
    long long numberOfWeeks(vector<int>& milestones) {
        sort(begin(milestones), end(milestones));
        int i = 0, j = milestones.size() - 1;
        long long ans{};
        while(i < j) {
            if(milestones[j] >= milestones[i]) {
                milestones[j] -= milestones[i];
                ans += 2 * milestones[i];
                i++;
            } else {
                milestones[i] -= milestones[j];
                ans += milestones[j] * 2;
                j--;
            }
        }
        if(milestones[i] != 0) ans++;
        return ans;
    }
};
/*
     0, 1, 2
    [1, 2, 3]

    2, _, 2, _, 2,_
    2, 1, 2, 1, 2, 0

    0,  1, 2
    [5, 2, 1]

    0, _, 0, _, 0, _, 0, _, 0, _
    0, 2, 0, 1, 0, 1, 0

    [4, 3, 3]
    0, _, 0, _, 0, _, 0, _
    0, 2, 0, 2, 0, 2,
*/
