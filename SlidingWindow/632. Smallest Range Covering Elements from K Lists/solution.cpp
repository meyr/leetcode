/*
 *  使用vector<pair<int, int>> 將所有list中的number全部放入並加上group的訊息
 *  排序後使用slinding window來判斷是否有範圍符合k == nums.size()
 *  
 *  time  : O(N + NlogN + N) = O(NlogN) , N 為所有nums個數總和
 *  space : O(N + logN + N) = O(N)
 */
class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {
        vector<pair<int, int>> m;
        for(int g = 0; g < nums.size(); ++g)
            for(auto& n : nums[g])
                m.push_back(make_pair(n, g));
        sort(begin(m), end(m));
        vector<int> ans{m.front().first, m.back().first};
        unordered_map<int, int> count;
        int k{};
        for(int left = 0, right = 0; right < m.size(); ++right) {
            auto& [nr, gr] = m[right];
            if(count[gr]++ == 0) k++;
            while(k == nums.size()) {
                auto& [nl, gl] = m[left++];
                if(ans[1] - ans[0] > nr - nl) {
                    ans[0] = nl;
                    ans[1] = nr;
                }
                if(--count[gl] == 0) k--;
            }
        }
        return ans;
    }
};
