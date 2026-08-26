/*
 *      使用slinding window計算substring的1的數量
 *      因為beautiful string的條件式 1的數量 == k
 *      所以使用while loop 的時候 必須檢查sum是否為k
 *      因為min(rtn, sub) 無法判斷長度 所以要自己判斷
 *
 *
 *      time  : O(N)
 *      space : O(N)
 */
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int sz = s.size();
        string rtn(sz + 1, '1');
        for(int left = 0, right = 0, sum = 0; right < sz; ++right) {
            sum += s[right] == '1';
            if(right >= k - 1) {
                while(sum >= k) {
                    if(sum == k) {
                        int len = right - left + 1;
                        string sub = s.substr(left, right - left + 1);
                        if(len < rtn.size()) rtn = sub;
                        else if(len == rtn.size()) rtn = min(rtn, sub);
                    }
                    sum -= (s[left] == '1');
                    left++;
                }
            }
        }
        if(rtn == string(sz + 1, '1')) return "";
        else return rtn;
    }
};
/*
 *      使用prefix sum但是要注意0的情況
 *
 *      time  : O(N)
 *      space : O(N)
 */
class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int sz = s.size();
        string rtn(sz + 1, '1');
        unordered_map<int, int> mp;
        for(int i = 0, sum = 0; i < sz; ++i) {
            sum += s[i] == '1';
            int left{-1};
            if(sum == k) {
                if(mp.count(0)) left = mp[0] + 1;
                else left = 0;
            } else if(mp.count(sum - k)) left = mp[sum - k] + 1;
            if(left != -1) {
                int len = i - left + 1;
                if(len < rtn.size()) rtn = s.substr(left, len);
                else if(len == rtn.size()) rtn = min(rtn, s.substr(left, len));
            }
            mp[sum] = i;
        }
        return rtn.size() == sz + 1 ? "" : rtn;
    }
};
