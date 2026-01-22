class RandomizedCollection {
    unordered_map<int, set<int>> um; //value, index
    vector<int> values;
public:
    RandomizedCollection() {

    }

    bool insert(int val) {
        bool rtn = um.count(val) == 0; // not present return true
        um[val].insert(values.size());
        values.push_back(val);
        return rtn;
    }

    bool remove(int val) {
        bool rtn = um.count(val); // present return true
        if(!rtn) return rtn;      // not present return directly
        auto it = prev(um[val].end());
        int idxToRemove = *it; // select one index from um[val]
        int back = values.back();
        if(back == val) { // if val == values.back()
            if(um[val].size() == 1) um.erase(val);
            else um[val].erase(it);
            values.pop_back();
        } else {
            if(um[back].size() == 1) um.erase(back);
            else um[back].erase(values.size() - 1);
            um[back].insert(idxToRemove);
            if(um[val].size() == 1) um.erase(val);
            else um[val].erase(it);
            values.pop_back();
            values[idxToRemove] = back;
        }

        return rtn;
    }

    int getRandom() {
        int idx = rand() % values.size();
        return values[idx];
    }
};
