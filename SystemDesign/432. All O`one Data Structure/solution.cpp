/*  必須小心使用map或是set 如果不存在的值存取會建立一個新的element
 *  例如: map<int, int> mp;
 *        int count = mp[3]; // 因為mp裡面沒有3 所以會建立 {3, 0}, 之後count才會等於0
 *                           // 但是當getMaxKey或是getMinKey就會出錯
 *
 */

class AllOne {
    unordered_map<string, int> um; // string, count
    map<int, set<string>> rank; // count, string
public:
    AllOne() {

    }

    void inc(string key) {
        if(um.count(key)) {     // 有這個數值
            int count = um[key];
            if(rank[count].size() == 1) rank.erase(count);
            else rank[count].erase(key);
        }
        um[key]++;
        rank[um[key]].insert(key);
    }

    void dec(string key) {      // 題目保證呼叫dec(key)裡面一定會有key 所以不用檢查 直接取得count
        int count = um[key]--;
        if(um[key] == 0) um.erase(key);
        if(rank[count].size() == 1) rank.erase(count);
        else rank[count].erase(key);
        if(um.count(key))
            rank[um[key]].insert(key);
    }

    string getMaxKey() {
        if(rank.empty()) return "";
        else return *(rank.rbegin()->second.begin());
    }

    string getMinKey() {
        if(rank.empty()) return "";
        else return *(rank.begin()->second.begin());
    }
};
