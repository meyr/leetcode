/*
 *  參考 : https://leetcode.cn/problems/naming-a-company/solutions/2924661/gong-si-ming-ming-by-leetcode-solution-v1s3/
 *
 *  使用第一個char來分組 unordered_map<char, unordered_set<string>> names; // 1st char, substr(1)
 *  群組兩兩互相組合成一個新的company name
 *
 *
 */
class Solution {
public:
    long long distinctNames(vector<string>& ideas) {
        unordered_map<char, unordered_set<string>> names;
        for (const string& idea: ideas) {
            names[idea[0]].insert(idea.substr(1, idea.size() - 1));
        }

        auto get_intersect_size = [](const unordered_set<string>& a, const unordered_set<string>& b) -> size_t {
            size_t ans = 0;
            for (const string& s: a) {
                if (b.count(s)) {
                    ++ans;
                }
            }
            return ans;
        };

        long long ans = 0;
        for (auto&& [pre_a, set_a]: names) {     // 群組兩兩組合成新的name
            for (auto&& [pre_b, set_b]: names) {
                if (pre_a == pre_b) {   // 如果第一個char一樣 一定不能組合
                    continue;
                }
                int intersect = get_intersect_size(set_a, set_b); // 計算倆倆之間相同的substring 有多少個 這些不能使用
                                                                  // 因為第一個char交換後會變成ideas裡面有的string  
                ans += static_cast<long long>(set_a.size() - intersect) * (set_b.size() - intersect);
            }
        }
        return ans;
    }
};
