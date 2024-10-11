/*
 *  參考 : https://leetcode.cn/problems/the-number-of-the-smallest-unoccupied-chair/solutions/895434/zui-xiao-wei-bei-zhan-ju-yi-zi-de-bian-h-kz2d/
 *
 *  因為player <= 1e4 所以最多使用1e4個chair
 *  可以把所有的號碼都丟進minheap 
 *  相關題目可以參考 1845. Seat Reservation Manager
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        map<int, set<int>> m; // time, arrival or leaving
        int t_arrival = times[targetFriend][0]; // __important__ 因為要讓targetFrient拿到最小的chair所以必須先知道arrival time
                                                //               當此時間到 第一個拿到的chair就是分配給targetFriend        
                                                
        for(int i = 0; i < times.size(); ++i) { // 因為player有0 所以+1
            m[times[i][0]].insert(i + 1);
            m[times[i][1]].insert(-(i + 1));
        }
        priority_queue<int, vector<int>, greater<>> avaliable; // avaliable seats
        unordered_map<int, int> seats; // player, no of seat occupied
        for(int i = 0; i < times.size(); ++i) avaliable.push(i);   // __important__ 把所有號碼都丟進minheap
        for(auto& ref : m) {
            for(auto& p : ref.second) {
                if(p < 0) {
                    avaliable.push(seats[-p]);
                } else {
                    int n = avaliable.top(); avaliable.pop();
                    if(ref.first == t_arrival) return n;
                    seats[p] = n;
                }
            }
        }
        return -1;
    }
};

/*
 *  參考其他答案
 *  有個重點是 把{leaving time, seat no} 丟進minheap 這樣就知道某個時間一到有多少的seat會釋出
 *
 *  和上面答案不同的是怎麼處理leaving time
 *
 *  time  : O(NlogN)
 *  space : O(N)
 */
class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> leaving; // 離開時間, no of occupied seat
        priority_queue<int, vector<int>, greater<>> avaliable; // 可以釋出seats
        int t_arrival = times[targetFriend][0];
        sort(begin(times), end(times));
        avaliable.push(0);
        for(auto& t : times) {
            // 到了此時間t[0] 先把已經離開的丟入avaliable
            while(!leaving.empty() && leaving.top().first <= t[0]) {
                auto [time, seat] = leaving.top(); leaving.pop();
                avaliable.push(seat);
            }
            if(avaliable.size() == 1) avaliable.push(avaliable.top() + 1); // __important__ 因為剩一個表示號碼都被拿光了 必須擴充
            int n = avaliable.top(); avaliable.pop();
            if(t[0] == t_arrival) return n;
            leaving.push(make_pair(t[1], n)); // 這個號碼可以被釋出的時間
        }
        return -1;
    }
};
