/* 模擬題目的意思 因為每遇到一個num就是把上一次的結果全部拿出來再or一次
 *
 *  1, 2, 4
 *  001              [1]
 *     010           [1, 2][2]
 *         100       [1, 2, 4][2, 4][4]
 *
 *   time  : O(N^2)
 *   space : O(N)
 */
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        unordered_set<int> ans;
        unordered_set<int> prev;
        for(const auto& n : arr) {
            unordered_set<int> cur;
            for(const auto& ref : prev)
                cur.insert(ref | n);
            cur.insert(n);
            ans.insert(begin(cur), end(cur));
            prev = move(cur);
        }
        return ans.size();
    }
};
