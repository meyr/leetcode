/*  先統計每個數字出現的頻率 
 *  從最大頻率的開始刪除
 *  
 *  time  : O(N + NlogN + N) = O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    int minSetSize(vector<int>& arr) {
        unordered_map<int, int> m;
        for(auto& n : arr) m[n]++;
        map<int, int> freq;
        for(auto& ref : m) freq[ref.second]++;
        int ans{}, remain = arr.size();
        for(auto it = freq.rbegin(); it != freq.rend(); ++it) {
            int target = remain - arr.size() / 2;
            if(target <= 0) break;
            int select = min((target + it->first - 1)/it->first, it->second);
            remain -= select * it->first;
            ans += select;
        }
        return ans;
    }
};
