/*  參考hint, 只要檢查 nums[i] - k, nums[i], nums[i] + k
 *
 *  why? 因為Greedy method 當nums[i] - k 或是 nums[i] + k 可以向上或是向下包刮最多的數
 *       反正一次operation可以加上[-k, k] 所以選擇包括最多數字的範圍
 *
 */
class Solution {
    int check(map<long, int>& mp, long target, int op) {
        if(seen.count(target)) return 0;    // 已經檢查過了
        seen.insert(target);
        int rtn{};
        auto it = mp.find(target);
        // 先找出 target的個數                                  // __important__ 不可以使用mp[target] 因為 mp[target] 會回傳T&, 如果宣告const map& 就不能使用
        int target_count{};                                     //               另外使用mp[target] 等於在mp內抽入target數值 如果target不存在的話 
        if(it == mp.end()) target_count = 0;                    //               會造成 for(auto& [val, _] : ) 形成infinite loop
        else if(it == mp.begin()) target_count = it->second;
        else target_count = it->second - prev(it)->second;

        // 找出上下兩個邊界
        auto right = mp.upper_bound(target + k);
        if(right != mp.begin()) right = prev(right);
        auto left = mp.lower_bound(target - k);
        int cnt = right->second - (left == mp.begin() ? 0 : prev(left)->second) - target_count; // 因為target不用轉換所以扣掉
        rtn = target_count + min(cnt, op);
        return rtn;
    }
    int k;
    unordered_set<long> seen;
public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        map<long, int> mp;   // value, count
        for(auto& n : nums) mp[n]++;                            // 統計每個數字個數
        if(mp.size() == 1) return nums.size();                  // special case
        for(auto it = mp.begin(); it != prev(mp.end()); ++it)   // 計算prefix sum
                next(it)->second += it->second;
        int ans{1};
        this->k = k;
        for(auto [val, _] : mp) {                               // 檢查每個數字 n - k, n, n + k
            ans = max(ans, check(mp, val - k, numOperations));
            ans = max(ans, check(mp,     val, numOperations));
            ans = max(ans, check(mp, val + k, numOperations));
        }
        return ans;
    }
};
/*  上面解答還要考慮是否是begin()再往前 可以在map上直接insert一個<LLONG_MIN, 0> element 可以避免檢查
 *
 */
class Solution {
    int check(long target) {
        if(seen.count(target)) return 0;
        seen.insert(target);
        int rtn{};
        int target_count = count.find(target) != count.end() ? count[target] : 0;
        auto right = prev(pfs.upper_bound(target + k));
        auto left = pfs.lower_bound(target - k);
        int cnt = right->second - prev(left)->second - target_count;
        rtn = target_count + min(cnt, op);
        return rtn;
    }
    int k, op;
    unordered_set<long> seen;
    map<int, int> count;    // 把count, pfs分開來 避免要從pfs找count數
    map<long, int> pfs;         

public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        for(auto& n : nums) count[n]++;
        if(count.size() == 1) return nums.size();
        pfs[LLONG_MIN] = 0;                                     // 插入一個最小值 避免檢查是否為begin
        for(auto it = count.begin(); it != count.end(); ++it)
                pfs[it->first] = prev(pfs.end())->second + it->second;
        int ans{1};
        this->k = k;
        this->op = numOperations;
        for(auto [val, _] : count) {
            ans = max(ans, check(val - k));
            ans = max(ans, check(    val));
            ans = max(ans, check(val + k));
        }
        return ans;
    }
};
