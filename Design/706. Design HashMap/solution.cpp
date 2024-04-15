/*
 *  使用list<pair<int, int>> 方便刪除element
 *
 */

class MyHashMap {
    vector<list<pair<int, int>>> tables;
    int getHash(int key) {
        return key * 1911 % 1024;
    }
public:
    MyHashMap() {
        tables.resize(1024);
    }
    
    void put(int key, int value) {
        int hash = getHash(key);
        int found{};
        for(auto& [k, v] : tables[hash]) {
            if(k == key) {
                v = value;
                found = true;
                break;
            }
        }
        if(!found) tables[hash].push_back(make_pair(key, value));
    }
    
    int get(int key) {
        int hash = getHash(key);
        for(auto& [k, v] : tables[hash]) {
            if(k == key) return v;
        }
        return -1;        
    }
    
    void remove(int key) {
        int hash = getHash(key);
        for(auto it = tables[hash].begin(); it != tables[hash].end(); ++it) {
            if(it->first == key) {
                tables[hash].erase(it);
                break;
            }
        }
    }
};
