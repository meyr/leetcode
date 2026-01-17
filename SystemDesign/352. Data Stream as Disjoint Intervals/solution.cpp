/*
 *   使用map紀錄interval 但是加入[-2, -2] 當成開頭可以避掉很多判斷
 *   考慮4種情況 1.前後可以接再一起 
                 2.和前面接再一起 
                 3.和後面接再一起
                 4.自己一個Interval
 */
class SummaryRanges {
    map<int, int> mp; // start, end
public:
    SummaryRanges() {
        mp[-2] = -2;
    }
    
    void addNum(int value) {
        auto it = mp.upper_bound(value);
        if(prev(it)->second >= value) return;
        else if(prev(it)->second == value - 1 && it->first == value + 1) {
            prev(it)->second = it->second;
            mp.erase(it);
        } else if(prev(it)->second == value - 1)
            prev(it)->second = value;
        else if(it->first == value + 1) {
            mp[value] = it->second;
            mp.erase(it);
        } else
            mp[value] = value;
    }
    
    vector<vector<int>> getIntervals() {
        vector<vector<int>> rtn;
        for(auto it = next(mp.begin()); it != mp.end(); ++it)
            rtn.push_back({it->first, it->second});
        return rtn;
    }
};
