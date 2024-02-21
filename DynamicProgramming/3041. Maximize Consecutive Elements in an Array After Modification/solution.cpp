/*
	why dynamic programming?
	因為每增加一個element，可以根據之前的結果來得到

*/
class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(begin(nums), end(nums)); //O(NlogN)
        unordered_map<int, int> m; //value, length
        int ans{1};
        for(auto& n : nums) { // O(N)
            if(m.count(n)) {
                m[n + 1] = max(m[n + 1], m[n] + 1);
                ans = max(ans, m[n + 1]);
            }
            if(m.count(n - 1)) {
                m[n] = max(m[n], m[n - 1] + 1);
                ans = max(ans, m[n]);
            }
            m[n] = max(m[n], 1);
            m[n + 1] = max(m[n + 1], 1);
        }
        return ans;
        // time : O(NlogN + N) = O(NlogN)
        // space : O(logN + N)
    }
};
