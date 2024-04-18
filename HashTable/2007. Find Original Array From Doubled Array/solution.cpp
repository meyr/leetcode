class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        vector<int> ans;
        int sz = changed.size();
        if(sz % 2 == 1) return ans;
        sort(begin(changed), end(changed)); // O(NlogN)
        unordered_map<int, int> m; // value, count
        for(auto& n : changed) { // O(N)
            if(n % 2 == 1 || m[n / 2] == 0) m[n]++;
            else {
                ans.push_back(n / 2);
                m[n / 2]--;
            }
        }
        return ans.size() == sz / 2 ? ans : vector<int>();
        // time  : O(NlogN + N) = O(NlogN)
        // space : O(logN + N) = O(N)
    } 
};
