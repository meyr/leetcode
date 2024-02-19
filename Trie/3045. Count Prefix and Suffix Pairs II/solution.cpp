/*
	參考lee215答案 https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/solutions/4744547/java-c-python-trie/


    重點是: 字串abc __同時為__某個string 的prefix和suffix， abcxxxabc
                |_| ac                                      |_______| ac
                 |  bb                                       |_____|  bb
                |_| ca                                        |___|   ca

    其中，i = 0, j = n - 1 - 0, ac  <-->   ac
          i = 1, j = n - 1 - 1, bb  <-->   bb
          i = 2, j = n - 1 - 2, ca  <-->   ca

    所以建立Trie的時候，只需考慮w[i], w[n - 1 - i], 其中n = w.size()
*/

class Solution {
    struct node{
        unordered_map<int, node*> m;
        int count;
    };
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        node* root = new node();
        long long ans{};
        for(const auto& w : words) {
            node* p = root;
            for(int i = 0, n = w.size(); i < n; ++i) {
                int val = w[i] * 128 + w[n - 1 - i];
                p = p->m.insert({val, new node()}).first->second;
                // 上面這行等同下面的意思，因為insert會return pair<iterator, bool>
                //if(!p->m.count(val)) p->m[val] = new node();
                //p = p->m[val];
                ans += p->count;
            }
            p->count++;
        }
        return ans;
    }
};
