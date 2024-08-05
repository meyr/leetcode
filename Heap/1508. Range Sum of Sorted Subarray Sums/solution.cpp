/*
 *  參考解答
 *
 *  這題的題目是對"sorted array" 做處理。 因為是sorted array[1, 2, 3, 4]
 *  從1開始的subarray : [1], [1, 2], [1, 2, 3], [1, 2, 3, 4] ==> subarray sum = [1, 3, 6, 10]
 *  從2開始的subarrry : [2], [2, 3], [2, 3, 4] ==> subarray sum = [2, 5, 9]
 *  從3開始的subarray : [3], [3, 4] ==> subarray sum = [3, 7]
 *  從4開始的subarray : [4] ==> subarray sum = [4]
 *
 *  最小的subarray sum一定是只有一個element也就是 [1][2][3][4] 其中一個
 *  但是第二小的subarray sum就有可能是一個element也有可能是兩個element組合起來的
 *  使用minheap的好處是可以先確定最小的 再從最小的推到下一個subarray sum
 *
 */
class Solution {
public:
    int rangeSum(vector<int>& nums, int n, int left, int right) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for(int i = 0; i < nums.size(); ++i)
            pq.push({nums[i], i + 1});
        int ans{};
        for(int i = 1; i <= right; ++i) { // 因為每執行一次得到第ith小的subarray sum 所以要執行 right 次
            auto [v, nxt] = pq.top(); pq.pop();
            if(i >= left) ans = (ans + v) % (int)(1e9 + 7);
            if(nxt < nums.size())
                pq.push({v + nums[nxt], nxt + 1}); // 根據目前的subarray得到下一個subarray sum
        }
        return ans;
    }
};
