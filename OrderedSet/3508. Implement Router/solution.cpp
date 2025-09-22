class Router {
    map<vector<int>, int> um;   // 檢查是否有重複packet的情況, <source, destination, timestamp>, status 其中status表示有沒有此packet
                                //                             status == 0 當沒有的時候不進行刪除 可以增加效率
    int limit;
    queue<vector<int>> q;       // 依進來順序排序 因為題目提到timestamp是持續增加
    unordered_map<int, deque<int>> dest;    // 根據destination, 把進來的packet的timestamp丟進來 方便查詢每個區間的packet數量
public:
    Router(int memoryLimit) : limit(memoryLimit) {
        
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        vector vec{source, destination, timestamp};
        // 檢查是否有重複
        if(um[vec]) return false;
        // 如果滿了 丟掉最舊packet
        if(q.size() == limit) forwardPacket();
        um[vec] = 1;
        q.push({source, destination, timestamp});
        dest[destination].push_back(timestamp);
        return true;
    }
    
    vector<int> forwardPacket() {
        if(q.size() == 0) return {};
        auto rtn = q.front(); q.pop();
        um[rtn] = 0;
        auto& ms = dest[rtn[1]];
        //只需要丟掉最早的timestamp
        ms.pop_front();
        return rtn;
    }
    
    int getCount(int destination, int startTime, int endTime) {
        if(!dest.count(destination)) return 0;
        auto& ms = dest[destination];
        // special cast不需要特別計算
        if(ms.size() == 0 || endTime < *ms.begin() || startTime > *ms.rbegin()) return 0;
        auto it1 = upper_bound(begin(ms), end(ms), endTime);
        auto it2 = lower_bound(begin(ms), end(ms), startTime);
        return distance(it2, it1);
    }
};
