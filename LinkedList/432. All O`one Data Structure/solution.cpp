/*
 *  參考解答
 *  https://leetcode.cn/problems/all-oone-data-structure/solutions/1335680/quan-o1-de-shu-ju-jie-gou-by-leetcode-so-7gdv/
 *
 *  time  : O(1) 如題目所示
 */
class AllOne {
    list<pair<unordered_set<string>, int>> lst; // double linked list每一個node都是儲存count從小到大
    /*
        lst
        |
        |--> [ { "apple", "banana", "cherry" }, 1 ]
        |
        |--> [ { "dog", "cat" }, 2 ]
        |
        |--> [ { "red", "green", "blue" }, 3 ]
    */
    //從string找到在lst中哪個element
    unordered_map<string, list<pair<unordered_set<string>, int>>::iterator> nodes; 

public:
    AllOne() {}

    void inc(string key) {
        if (nodes.count(key)) {
            auto cur = nodes[key], nxt = next(cur);
            //把element搬到下一個
            if (nxt == lst.end() || nxt->second > cur->second + 1) {
                unordered_set<string> s({key});
                nodes[key] = lst.emplace(nxt, s, cur->second + 1);
            } else {
                nxt->first.emplace(key);
                nodes[key] = nxt;
            }
            //清除目前的element
            cur->first.erase(key);
            if (cur->first.empty()) {
                lst.erase(cur);
            }
        } else { // key 不在链表中
            if (lst.empty() || lst.begin()->second > 1) {
                unordered_set<string> s({key});
                lst.emplace_front(s, 1);
            } else {
                lst.begin()->first.emplace(key);
            }
            nodes[key] = lst.begin();
        }
    }

    void dec(string key) {
        auto cur = nodes[key];
        // count == 1直接移除掉
        if (cur->second == 1) { // key 仅出现一次，将其移出 nodes
            nodes.erase(key);
        } else {
            //搬到前一個
            auto pre = prev(cur);
            if (cur == lst.begin() || pre->second < cur->second - 1) {
                unordered_set<string> s({key});
                nodes[key] = lst.emplace(cur, s, cur->second - 1); // 使用iterator的話，insert或是emplace都會向前插入
                // 要向後插入需要取得下一個element的iterator在使用insert或是emplace
            } else {
                pre->first.emplace(key);
                nodes[key] = pre;
            }
        }
        cur->first.erase(key);
        if (cur->first.empty()) {
            lst.erase(cur);
        }
    }

    string getMaxKey() {
        return lst.empty() ? "" : *lst.rbegin()->first.begin();
    }

    string getMinKey() {
        return lst.empty() ? "" : *lst.begin()->first.begin();
    }
};
