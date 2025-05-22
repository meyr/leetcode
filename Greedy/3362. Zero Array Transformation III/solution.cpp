/*  參考 : https://leetcode.com/problems/zero-array-transformation-iii/solutions/6737791/zero-array-transformation-iii-by-leetcod-1w7n/
 *
 *  一樣使用prefix sum概念 但是這次是要找出最少的queries
 *
 *  Greedy point : 因為要找出最少的queries 所以取一個query應該是__越廣越好__
 *                 但是我們使用prefix sum所以要先針對 __起點排序__
 *
 *                 maxheap 是讓我們從看過的queries中 挑一個最廣的出來
 *
 *
 *  time  : O(NlogN + N(M + logM)) = O(NlogN + MN)
 *  space : O(logN + M + M) = O(logN + M)
 */
class Solution {
public:
    int maxRemoval(vector<int>& nums, vector<vector<int>>& queries) {
        sort(begin(queries), end(queries), [](auto& a, auto& b){  // 起點排序
            return a[0] < b[0];
        });
        priority_queue<int> pq; //max heap 取出最遠範圍的index(Greedy point)
        unordered_map<int, int> m;
        for(int i = 0, j = 0, cur = 0; i < nums.size(); ++i) {
            cur += m[i];
            while(j < queries.size() && queries[j][0] == i)          // 把目前index = i 所遇到的queries都丟進去heap
                pq.push(queries[j++][1]);
            while(!pq.empty() && cur < nums[i] && pq.top() >= i) {   // 從heap中選一個最寬的range
                cur++;
                m[pq.top() + 1]--;
                pq.pop();
            }
            if(cur < nums[i]) return -1;
        }
        return pq.size(); // heap中剩下的就是沒用到的
    }
};
