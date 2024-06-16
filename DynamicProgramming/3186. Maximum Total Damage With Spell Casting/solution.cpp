/*
 *  每個power[i]都有兩個狀態 cast 和 no-cast
 *  當power[i] == power[i + 1] 就可以合併先拿
 *  no-cast 就可以從power[i] != power[j] 開始
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    long long helper(vector<int>& power, int idx) {
        if(~mem[idx]) return mem[idx]; 
        long long tmp = power[idx];
        int nxt = idx + 1;
        while(nxt < power.size() && power[nxt] == power[idx])
            tmp += power[nxt++];
        long long notake = helper(power, nxt);
        while(nxt < power.size() && power[nxt] <= power[idx] + 2) ++nxt;
        long long take = helper(power, nxt) + tmp;
        return mem[idx] = max(notake, take);
    }
    vector<long long> mem;
public:
    long long maximumTotalDamage(vector<int>& power) {
        sort(begin(power), end(power));
        mem.resize(power.size() + 1, -1);
        mem.back() = 0;
        return helper(power, 0);
    }
};
