/*
 *  因為題目說每次boat最多可以載兩個人 所以最小的情況是ceil(people.size() / 2)
 *  Greedy point : 盡量每次都載兩個人
 *        
 *  1. 先排序
 *  2. 確定最大和最小是否可以配對
 *  3. 不行就只載最大的
 */

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(begin(people), end(people));
        int i = 0, j = people.size() - 1;
        int ans{};
        while(i <= j) {
            if(people[i] + people[j]  <= limit) // 如果有可以載兩個人就載
                i++;
            ans++;
            j--;
        }
        return ans;
    }
};
