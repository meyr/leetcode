/*
 *  Greedy point : 每次都取剩下最多task來處理
 *                 因為需要idle所以放入vector中, 計算還需要放回pq處理的各數, 並放回pq
 *
 *  time  : O(N + NlogN) = O(NlogN)
 *  space : O(1) 固定26個字母大小 
 */

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        // special case
        if(n == 0) return tasks.size();
        unordered_map<char, int> freq; //task, count
        for(auto& t : tasks) freq[t]++; //O(N), N : size of tasks

        auto cmp = [&](auto& a, auto& b) {
            return freq[a] < freq[b];
        };
        priority_queue<char, vector<char>, decltype(cmp)> pq(cmp);
        for(auto& ref : freq) pq.push(ref.first); //O(1)

        int ans{};
        while(!pq.empty()) { // O(NlogN)
            vector<char> tmp;
            while(!pq.empty() && tmp.size() < n + 1) { // 一次處理一個週期
                char task = pq.top(); pq.pop();
                tmp.push_back(task);
                freq[task]--;
            }
            int count{}; // 還要處理的task個數
            for(auto& c : tmp) {
                if(freq[c] != 0) {
                    pq.push(c);
                    count++;
                }
            }
            if(count == 0) ans += tmp.size(); // 沒有需要處理的task
            else ans += n + 1;
        }
        return ans;
    }
};
