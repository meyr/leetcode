/*  使用set來記錄每個座位
 *  並且每次都檢查 seat0 和 seatN-1
 *
 */
class ExamRoom {
    set<int> st;
    int n;
public:
    ExamRoom(int n) {
        this->n = n;
    }

    // O(N + logN)
    int seat() {
        int rtn{-1}, space{};
        if(st.empty())  rtn = 0;
        else {
            auto it = st.begin();
            if(*it > space) {
                space = *it;
                rtn = 0;
            }
            it++;
            for(; it != st.end(); ++it) {
                if((*it - *prev(it)) / 2 > space) {
                    space = (*it - *prev(it)) / 2;
                    rtn = *prev(it) + space;
                }
            }
            if(n - 1 - *st.rbegin() > space) {
                rtn = n - 1;
            }
        }
        st.insert(rtn);
        return rtn;
    }
    
    // O(logN)
    void leave(int p) {
        st.erase(p);
    }
};
