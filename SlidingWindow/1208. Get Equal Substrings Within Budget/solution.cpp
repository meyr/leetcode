/*
    a b c d
    b c d f
    1 1 1 1

    a, b, c, d
    c, d, e, f
    2, 2, 2, 2
    
    1. 先找出每個index的cost
    2. 使用slinding window控制window中的cost <= maxCost

    time  : O(N)
    space : O(N)

*/
class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int sz = s.size();
        vector<int> cost(sz);
        for(int i = 0; i < sz; ++i)
            cost[i] = abs(s[i] - t[i]);
        int ans{}, cur{};
        for(int left = 0, right = 0; right < sz; ++right) {
            cur += cost[right];
            while(left < right && cur > maxCost)
                cur -= cost[left++];
            if(cur <= maxCost)
                ans = max(ans, right - left + 1);
        }
        return ans;
    }
};

// 根據上面的做法 只用maxCost來節省空間
// time  : O(N)
// space : O(1)
class Solution {
public:
    int equalSubstring(string s, string t, int maxCost) {
        int left = 0, right = 0, ans{};
        for(int left = 0, right = 0; right < s.size(); ++right) {
            maxCost -= abs(s[right] - t[right]);
            while(left < right && maxCost < 0)
                maxCost += abs(s[left] - t[left++]);
            if(maxCost >= 0) ans = max(ans, right - left + 1);
        }
        return ans;
    }a
};
