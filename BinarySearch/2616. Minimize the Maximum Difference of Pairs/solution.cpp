/*  一開始想法使用greedy 但是錯了
 *
 *  1. 先找出數字一樣扣掉 (有可能不是先扣0 所以錯了)
 *  2. 再找出相鄰數字差
 *
 *  time  : O(NlogN + N + NlogP)
 *  space : O(N + P)
 */
class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        if(p == 0) return 0;
        map<int, int> m;
        for(auto& n : nums) m[n]++;
        for(auto& ref : m) {
            p -= ref.second / 2;
            if(ref.second % 2 == 0)
                m.erase(ref.first);
            else
                ref.second = ref.second % 2;
            if(p <= 0) return 0;
        }
        priority_queue<int> pq;// maxheap
        for(auto it = next(m.begin()); it != m.end(); ++it) {
            pq.push(it->first - prev(it)->first);
            if(pq.size() > p)
                pq.pop();
        }
        return pq.top();
    }
};
/*  參考hint使用DP 但是MLE
 *
 *  time  : O(NP)
 *  space : O(NP)
 */
class Solution {
    int helper(vector<int>& nums, int p, int idx) {
        int rtn;
        if(~mem[p][idx]) return mem[p][idx];
        else if(p == 0) rtn = 0;
        else if(idx >= nums.size() - 1) rtn = p ? 1e9 : 0;
        else {
            rtn = min({helper(nums, p, idx + 1),                                        //  __very_important__   但是我們要總體的抉擇是最小值
                        max(helper(nums, p - 1, idx + 2), nums[idx + 1] - nums[idx])    //                       先找出有選擇的最大值 因為有選擇就必須計算相鄰間最大差值
                      });
        }
        return mem[p][idx] = rtn;
    }
    vector<vector<int>> mem;
public:
    int minimizeMax(vector<int>& nums, int p) {
        if(p == 0) return 0;
        sort(begin(nums), end(nums));
        mem.resize(p + 1, vector<int>(nums.size() + 1, -1));
        return helper(nums, p, 0);
    }
};
/*  minimum-maximum 問題就是使用binary search
 *
 *  ans : 0, 1, 2,  3, 4, 5
 *  cnt : 3, 4, 4, [5], 5, 6
 *              <   >=
 *
 *  time  : O(NlogN)
 *  space : O(logN) <-- sort
 */
class Solution {
public:
    int minimizeMax(vector<int>& nums, int p) {
        if(p == 0) return 0;
        sort(begin(nums), end(nums));
        int left = 0, right = nums.back() - nums.front();
        while(left < right) {
            int mid = left + (right - left) / 2;
            int cnt{};
            for(int i = 1; i < nums.size(); ++i) {
                if(nums[i] - nums[i - 1] <= mid) {
                    cnt++;
                    i++;
                }
            }
            if(cnt >= p) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
/*
*/
