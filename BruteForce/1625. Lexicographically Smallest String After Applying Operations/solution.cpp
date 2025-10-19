/* ref : https://leetcode.com/problems/lexicographically-smallest-string-after-applying-operations/solutions/899489/basic-dfs-brute-force-this-kind-of-quest-c0n7/ 
 *
 * 想太複雜了其實一開始應該先使用暴力破解
 * 而且這題的s.size() <= 100 更可以暴力破解
 * 怎麼暴力破解? 每次操作有兩種選擇 1. 奇位+a, 或是2. 旋轉b
 *
 */
class Solution {
    unordered_set<string> visited;
    bool isVisited(const string& s) {
        return visited.count(s);
    }
    void visit(const string& s) {
        ans = min(ans, s);
        visited.insert(s);
    }
    string rotate(string s, int x) { // 旋轉function
        reverse(begin(s), end(s));          // 為什麼這樣可以旋轉?
        reverse(begin(s), begin(s) + x);    // S = AB  (字串s可以拆成AB兩個部分)
        reverse(begin(s) + x, end(s));      // reverse(S) = reverse(AB) = r(B)r(A)
        return s;                           // 再對前後進行reverse = BA 達到向左選轉的效果
    }                                       // 如果要向右旋轉(x)就是 向左旋轉size(s) - x 
    string add(string s, int x) {   // 奇位+a function
        for(int i = 1; i < s.size(); i += 2) {
            char& c = s[i];
            c = '0' + (c - '0' + x) % 10;
        }
        return s;
    }
    string ans;
    int a, b;
    void dfs(string s) { // 每次操作rotate或是add選一種執行
        if(isVisited(s)) return;
        visit(s);
        dfs(rotate(s, b));      // 因為string s 都是call by value 所以下次再呼叫等於忽略前次的操作
        dfs(add(s, a));
    }
public:

    string findLexSmallestString(string s, int a, int b) {
        ans = s;
        this->a = a;
        this->b = b;
        dfs(s);
        return ans;
    }
};
