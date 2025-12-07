/*
 *  使用top down recursive + memorization 來統計次數
 *  time  : O(N^2) TLE
 */
 class Solution {
    int k, mod = 1e9 + 7;
    // helper : 找出從index往後看的組合數
    int helper(vector<int>& nums, int idx) {
        if(~mem[idx]) return mem[idx];
        long long cnt{0};
        int mxval = nums[idx], mnval = nums[idx];
        for(int i = idx; i < nums.size(); ++i) { // 往後找最大-最小<=k的組合然後切成下一個subarray
            mxval = max(mxval, nums[i]);
            mnval = min(mnval, nums[i]);
            if(mxval - mnval <= k)
                cnt = (cnt + helper(nums, i + 1)) % mod;
            else break;
        }
        return mem[idx] = cnt;
    }
    // f(idx) = f(idx, idx + 1, idx + 2, ...)
    vector<int> mem;
public:
    int countPartitions(vector<int>& nums, int k) {
        this->k = k;
        mem.resize(nums.size() + 1, -1);
        mem.back() = 1;
        return helper(nums, 0);
    }
};
/*
 *   把上述code改成buttom up tabulation 
 *   即使這樣也是O(N^2) TLE
 *   第二個for loop是要從index往後找到最後不成立的index
 */
 class Solution {
    int k, mod = 1e9 + 7;
public:
    int countPartitions(vector<int>& nums, int k) {
        this->k = k;
       vector<int> dp(nums.size() + 1);
       dp[nums.size()] = 1;
       for(int idx = nums.size() - 1; idx >= 0; --idx) {
            int mxval = nums[idx], mnval = nums[idx];
            for(int i = idx; i < nums.size(); ++i) { // 每次都從idx往後找到mxval - mnval > k 的點 因為每次都加一個num
                mxval = max(mxval, nums[i]);
                mnval = min(mnval, nums[i]);
                if(mxval - mnval <= k)
                    dp[idx] = (dp[idx] + dp[i + 1]) % mod;
                else break;
            }
       }
       return dp[0];
    }
};
/*
 *   每次都增加一個nums[idx] 所以使用兩個deque 一個是統計最大值 所以是從大到小
 *                                             一個是統計最小值 所以使從小大大
 *   注意: deque是放index而不是數值 因為我要知道 最後成立的index在哪
 */
deque<int> mx, mn;
int i = nums.size() - 1;
int j = nums.size() - 1;
// 每加入一個數值 就更新mx, mn queue
while(!mx.empty() && nums[mx.back()] <= nums[i])
    mx.pop_back();
mx.push_back(i);
while(!mn.empty() && nums[mn.back()] >= nums[i])
    mn.pop_back();
mn.push_back(i);
/* 0,1,2,3,4   k = 4
 * 9,4,1,3,7
 *     i   j    
 * mx :  7(4)
 * mn :  7(4)
 * 加入3
 * mx : 7(4), 3(3)          7 - 3 = 4
 * mn : 3(3)
 * 加入1
 * mx : 7(4), 3(3), 1(2)    7 - 1 = 5 > k  從j = 4開始丟如果mx.front()或是mn.front() >= j 就丟掉
 * mn : 1(2)
 *
 * j 是指向最後, 所以i~j是一個window來確認是否符合題目要求
 */
while(nums[mx.front()] - nums[mn.front()] > k) {
    if(mx.front() >= j) mx.pop_front();
    if(mn.front() >= j) mn.pop_front();
    j--;
}
/*  最後計算dp[i + 1] + ... + dp[j + 1] 使用prefix sum
 *  
 */
class Solution {
public:
    int countPartitions(vector<int>& nums, int k) {
        int sz = nums.size();
        int mod = 1e9 + 7;
        vector<int> dp(sz + 1, 0);
        vector<int> pfs(sz + 2, 0);
        dp[sz] = 1;
        pfs[sz] = 1;
        deque<int> mx, mn;
        for(int i = sz - 1, j = sz - 1; i >= 0; --i) {
            while(!mx.empty() && nums[mx.back()] <= nums[i]) mx.pop_back();
            while(!mn.empty() && nums[mn.back()] >= nums[i]) mn.pop_back();
            mx.push_back(i);
            mn.push_back(i);
            while(nums[mx.front()] - nums[mn.front()] > k) {
                if(mx.front() == j) mx.pop_front();
                if(mn.front() == j) mn.pop_front();
                j--;
            }
            // 核心邏輯補齊 (fixme 部分)
            // 對於當前起點 i，合法的切割點 x 可以是 i 到 j 之間的任意位置
            // 下一個狀態就是 dp[x+1]。
            // 所以 dp[i] = dp[i+1] + dp[i+2] + ... + dp[j+1]
            // 利用後綴和陣列 pfs 計算區間和： sum = pfs[start] - pfs[end + 1]
            // 我們需要的區間是 [i+1, j+1]
            
            long long current_ways = (long long)pfs[i + 1] - pfs[j + 2];
            
            // 處理負數取模 (因為減法可能導致負值)
            dp[i] = (current_ways % mod + mod) % mod;
            pfs[i] = (dp[i] + pfs[i + 1]) % mod;
        }
        
        return dp[0];
    }
};
