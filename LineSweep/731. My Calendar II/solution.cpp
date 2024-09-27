/*
 *  使用line sweep可以解決此問題 但是tc為O(N^2) 
 *
 *  雖然是暴力破解 但是對第一個答案也不失為好方法
 *  先給出暴力破解再慢慢改進
 *
 *  time  : O(N^2)
 *  sapce : O(N)
 */
class MyCalendarTwo {
    map<int, int> m;
public:
    MyCalendarTwo() {
        
    }
    
    bool book(int start, int end) {
        m[start]++;
        m[end]--;
        int val{};
        for(auto& ref : m) {
            val += ref.second;
            if(val > 2) {
                m[start]--;
                m[end]++;
                return false;
            }
        }
        return true;
    }
};
