/* 使用map紀錄interval
 *
 *  space : O(N)
 */
class MyCalendar {
    map<int, int> m;
public:
    MyCalendar() {
        
    }
  
    // time  : O(logN)
    bool book(int startTime, int endTime) {
        auto it = m.upper_bound(startTime);
        if(it != m.end() && it->first < endTime) return false;
        if(it != m.begin() && prev(it)->second > startTime) return false;
        m[startTime] = endTime;
        return true;
    }
};
