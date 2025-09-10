/*  ref : https://leetcode.cn/problems/minimum-number-of-people-to-teach/solutions/3766885/xu-yao-jiao-yu-yan-de-zui-shao-ren-shu-b-jaf9/
 *
 *  有兩種情況 1. 使用者A和使用者B有共同的語言 則我們可以忽略
 *             2. 使用者A和使用者B沒有共同的語言 紀錄這兩個使用者
 *
 *  Greedy point: 統計不能互通的使用者之間 所使用的最多語言是什麼 教其他使用者最多共同語言就是最少的次數
 *
 */
class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        unordered_set<int> cantCommSet;
        for(const auto& f : friendships) {
            vector<int>& lang0 = languages[f[0] - 1];
            vector<int>& lang1 = languages[f[1] - 1];
            unordered_set<int> lan(begin(lang0), end(lang0));
            bool canComm = any_of(begin(lang1), end(lang1), [&lan](int l){  // 檢查是否有共同的語言
                return lan.count(l);
            });
            if(!canComm) {
                cantCommSet.insert(f[0] - 1);
                cantCommSet.insert(f[1] - 1);
            }
        }
        vector<int> lang(n + 1);
        int maxcnt{};
        for(const auto& u : cantCommSet) {
            for(const auto& l : languages[u])
                maxcnt = max(maxcnt, ++lang[l]);
        }
        return cantCommSet.size() - maxcnt;
    }
};
