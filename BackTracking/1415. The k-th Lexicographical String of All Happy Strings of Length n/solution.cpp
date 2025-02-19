class Solution {
    bool helper(int n, int& k, string& ans) {
        if(n == 0) {
            return --k == 0;
        } else {
            char prev = ans.empty() ? 'z' : ans.back();
            for(char nxt : {'a', 'b', 'c'}) {
                if(nxt != prev) {
                    ans.push_back(nxt);
                    if(helper(n - 1, k, ans)) return true;
                    ans.pop_back();
                }
            }
            return false;
        }
    }
public:
    string getHappyString(int n, int k) {
        string ans{};
        helper(n, k, ans);
        return ans;
    }
};
