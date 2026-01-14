class LFUCache {
    unordered_map<int, int> values, count;
    unordered_map<int, list<int>::iterator> k2it;
    map<int, list<int>> freq;
    int sz{}, capacity;

    void drop_lfu_element()
    {
        auto it = freq.begin();
        int key = it->second.back();
        values.erase(key);
        count.erase(key);
        k2it.erase(key);
        it->second.pop_back();
        if(it->second.empty()) freq.erase(it->first);
        sz--;
    }

public:
    LFUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if(!k2it.count(key)) return -1;
        int rtn = values[key];
        auto it = k2it[key];
        int cnt = count[key];
        count[key]++;
        freq[cnt + 1].splice(freq[cnt + 1].begin(), freq[cnt], it);
        if(freq[cnt].empty()) freq.erase(cnt);
        return rtn;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;
        if(!k2it.count(key)) {
            if(sz == capacity) drop_lfu_element();
            sz++;
            values[key] = value;
            count[key] = 1;
            freq[1].push_front(key);
            k2it[key] = freq[1].begin();
        } else {
            values[key] = value;
            auto it = k2it[key];
            int cnt = count[key];
            count[key]++;
            freq[cnt + 1].splice(freq[cnt + 1].begin(), freq[cnt], it);
            if(freq[cnt].empty()) freq.erase(cnt);
        }
    }
};
