class Solution {
    // 參考lee215答案: https://leetcode.com/problems/furthest-building-you-can-reach/solutions/918515/java-c-python-priority-queue/ 

    // Greedy point:
    // 先使用ladders，
    // 沒了ladders再使用bricks
    // 如果bricks不夠，就從之前使用過ladders選一個最小的出來
    // 因為高度差小使用ladders太浪費了
public:
    int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
        int sz = heights.size();
        priority_queue<int> pq;// maxheap，但是推進去-d當成minheap使用
        for(int i = 0; i < sz - 1; ++i) { // O(NlogN)
            int d = heights[i + 1] - heights[i];
            if(d > 0) pq.push(-d); // 先使用ladders
            if(pq.size() > ladders) { // 超過最大的ladders
                bricks += pq.top(); // 改使用bricks
                pq.pop();
            }
            if(bricks < 0) return i;
        }
        return sz - 1;
        // time : O(NlogN)
        // space : O(N)
    }
};
