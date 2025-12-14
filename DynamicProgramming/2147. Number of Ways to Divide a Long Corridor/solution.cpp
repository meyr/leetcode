/*
 *  一開始覺得這是DP問題所以使用DP方法求解
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    int mod = 1e9 + 7;
    long long helper(string& cor, int idx) {
        if(~mem[idx]) return mem[idx];
        int nxt = idx, seats{};
        while(nxt < cor.size() && seats < 2) {
            seats += cor[nxt] == 'S';
            nxt++;
        }
        int cur = nxt;
        while(nxt < cor.size() && cor[nxt] == 'P') nxt++;
        if(nxt == cor.size()) return 1;
        else return mem[idx] = ((nxt - cur + 1) * helper(cor, nxt)) % mod;
    }
    vector<int> mem;
public:
    int numberOfWays(string corridor) {
        int count = count_if(begin(corridor), end(corridor), [](char& c){
            return c == 'S';
        });
        if(count < 2 || count % 2) return 0;
        else if(count == 2) return 1;
        else {
            mem.resize(corridor.size() + 1, -1);
            mem.back() = 1;
            return helper(corridor, 0);
        }
    }
};
/*  到頭來只是數seats中間的plants數目
 *  所以只要先記錄seat的index然後把中間的樹木相乘即可
 *  time  : O(N + K) = O(N), N : size of corridor, K : count of seats, N > K
 *  space : O(K)
 */
 class Solution {
public:
    int numberOfWays(string corridor) {
        vector<int> idxs;
        for(int i = 0; i < corridor.size(); ++i)
            if(corridor[i] == 'S')
                idxs.push_back(i);
        if(idxs.size() < 2 || idxs.size() % 2) return 0;
        else if(idxs.size() == 2) return 1;
        else {
            int mod = 1e9 + 7;
            long long ans{1};
            for(int i = 1; i < idxs.size() - 1; i += 2) {
                ans = (ans * (idxs[i + 1] - idxs[i])) % mod;
            }
            return ans;
        }
    }
};
