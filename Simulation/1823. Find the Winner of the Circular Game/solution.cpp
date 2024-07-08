/*
 *  使用set來模擬遊戲的進行
 *
 *  time  : O(N^2)
 *  space : O(N) 
 */
class Solution {
public:
    int findTheWinner(int n, int k) {
        set<int> s;
        for(int i = 1; i <= n; ++i) s.insert(i); // O(NlogN)
        auto st = s.begin();
        while(s.size() > 1) {   // O(N * (N + logN))
            int m = (k) % s.size();
            while(m--) {
                if(++st == s.end())
                    st = s.begin();
            }
            if(st == s.begin()) 
                s.erase(prev(s.end()));
            else
                s.erase(prev(st));
        }
        return *s.begin();
    }
};
/*
 *  參考解答可以使用queue來模擬
 *
 */
class Solution {
public:
    int findTheWinner(int n, int k) {
        queue<int> q;
        for(int i = 1; i <= n; ++i) q.push(i);
        while(q.size() > 1) {
            int x = k;
            while(x-- > 1) {
                q.push(q.front());
                q.pop();
            }
            q.pop();
        }
        return q.front();
    }
};
