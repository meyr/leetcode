/*
    另一個方法是使用hashtable紀錄以前看過的add number數目

    time  : O(N)
    space : O(N)
*/
class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        unordered_map<int, int> m{{0, 1}};
        int cnt{}, ans{};
        for(auto& n : nums) {
            cnt += n % 2;
            ans += m[cnt - k];
            m[cnt]++;
        }
        return ans;
    }
};
