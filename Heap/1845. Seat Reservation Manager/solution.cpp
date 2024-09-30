/*
 *  因為是找出最小值 所以使用minheap
 *
 *  time  : O(NlogN + P + QlogN) = O(P + (N+Q)logN), P: 呼叫reverve次數, Q: 呼叫unreserve次數 
 *  space : O(N)
 */
class SeatManager {
    priority_queue<int, vector<int>, greater<>> pq; //minheap
public:
    SeatManager(int n) { // O(NlogN)
        for(int i = 1; i <= n; ++i)
            pq.push(i);
    }
    
    int reserve() { // O(1)
        int rtn = pq.top();
        pq.pop();
        return rtn;
    }
    
    void unreserve(int seatNumber) { //O(logN)
        pq.push(seatNumber);
    }
};
