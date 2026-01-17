/*   使用unordered_map可以達到insert remove都是O(1)
 *   但是為了讓getRandom也是O(1) 多增加一個vector來儲存
 *   因為多了vector, 所以unordered_map改儲存value, index
 *
 */

class RandomizedSet {
    unordered_map<int, int> um; // value, index of values
    vector<int> values;
public:
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        bool rtn{false};
        if(!um.count(val)) {
            values.push_back(val);
            um[val] = values.size() - 1;
            rtn = true;
        }
        return rtn;
    }
    
    bool remove(int val) {
        bool rtn{false};
        if(um.count(val)) {
            int idx = um[val];
            int bk_val = values.back();
            swap(values[idx], values.back());
            values.pop_back();
            um[bk_val] = idx;
            um.erase(val);
            rtn = true;
        }
        return rtn;
    }
    
    int getRandom() {
        int r = rand() % values.size();
        return values[r];
    }
};
