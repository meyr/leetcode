/*
 *  如果沒size限制和LRU限制 只要使用unordered_map就可以搞定
 *  但是現在多了必須統計 Least Recently Used 也就是不管你呼叫 get()或是 put() 都要把最常使用的放到前頭
 *  這樣才有機會知道最後一個是誰 所以使用cpp的list
 *
 *  iterator就像是pointer指向某個struct 所以使用unordered_map來儲存key和指向list的iterator
 *
 */
class LRUCache {
    using lpii = list<pair<int, int>>;
    int sz;
    unordered_map<int, lpii::iterator> um; // key, list::iterator
    lpii lru;  // key, value
public:
    LRUCache(int capacity) {
        sz = capacity;
    }

    // time  : O(1)
    int get(int key) {
        if(um.count(key)) {
            auto it = um[key];
            int rtn = it->second;
            lru.splice(lru.begin(), lru, it);   // 把 it 搬到開頭
            return rtn;
        } else return -1;
    }

    // time  : O(1)
    void put(int key, int value) {
        if(um.count(key)) {
            auto it = um[key];
            lru.splice(lru.begin(), lru, it);
            it->second = value;
        } else {
            if(lru.size() == sz) {
                int key = lru.back().first;
                lru.pop_back();
                um.erase(key);
            }
            lru.push_front({key, value});
            um[key] = lru.begin();
        }
    }
};
