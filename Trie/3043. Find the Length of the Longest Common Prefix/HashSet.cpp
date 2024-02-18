
class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<string> s;
        for(auto& n : arr1) {
            string str = to_string(n);
            for(int len = 1; len <= str.size(); ++len)
                s.insert(str.substr(0, len));
        }
        int ans{};
        for(auto& n : arr2) {
            string str = to_string(n);
            for(int len = 1; len <= str.size(); ++len) {
                string sub = str.substr(0, len);
                if(s.count(sub)) ans = max(ans, (int)sub.size());
            }
        }
        return ans;
    }
};
