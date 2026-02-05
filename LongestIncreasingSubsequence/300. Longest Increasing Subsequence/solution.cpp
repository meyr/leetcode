class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> v;
        for(auto& n : nums) { // O(NlogN)
            auto it = lower_bound(begin(v), end(v), n);
            if(it == v.end()) v.push_back(n);
            else *it = n;
        }
        return v.size(); // O(N)

        // time : O(NlogN)
        // space : O(N)
    }
};
