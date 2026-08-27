/*
 *      一開始用最偷懶的方法 使用cpp內建的next_permutation來做
 *      想當然而就是TLE
 */
class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        sort(begin(s), end(s)); // 排完序後就是第一個最小的permutation 所以使用do-while loop
        do{
            if(s > target)
                return s;
        }while(next_permutation(s.begin(), s.end()));   // 把s變成下一個permutation
        return "";
    }
};
/*
 *      因為1 <= s.length == target.length <= 300 直覺就是backtrace,
 *      另外學習digit DP的作法 多了一個is_greater的變數 來判斷是否已經大於target
 *      如果已經大於target那後面只需要最小排列
 *      如果不是那就只能選等於target的字元 然後繼續往下排
 *      不然就是退回前一步 --> backtrace
 */
class Solution {
    vector<int> count;
    string str{};
    bool helper(string_view target, bool is_greater) {
        int sz = str.size();
        if(sz == target.size()) return is_greater;          // 長度已經到達 確認是否大於target
        if(is_greater) {                                    // 已經大於target那就把剩下的chars排列成最小排列 加到str後面
            string remain{};
            for(int i = 0; i < 26; ++i)
                if(count[i]) remain += string(count[i], i + 'a');
            str += remain;
            return true;
        }
        for(int i = target[sz] - 'a'; i < 26; ++i) {    // 只需要從target[sz] 開始尋找 因為目標是大於target
            if(count[i]) {
                str.push_back(i + 'a');
                count[i]--;
                if(helper(target, str.back() > target[sz])) // __important__ 判斷目前的str是否大於target
                    return true;                            // 已經找到了就直接返回
                count[i]++;
                str.pop_back();
            }
        }
        return false;
    }
public:
    string lexGreaterPermutation(string s, string target) {
        count.resize(26);
        for(auto& c : s) count[c - 'a']++;
        auto rtn = helper(target, 0);
        if(rtn && str > target) return str; // 有找到 且 str > target才輸出
        else return "";
    }
};
