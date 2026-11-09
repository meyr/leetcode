/*
 *      使用minheap來追蹤已經結束的server
 *      使用set存放free server並且使用lower_bound來找出下一個number
 *
 */

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        priority_queue<vector<int>, vector<vector<int>>, greater<>> busy; // time, index
        unordered_map<int, int> count;
        int sz = arrival.size();
        for(int i = 0; i < min(k, sz); ++i) {
            busy.push({arrival[i] + load[i], i});
            count[i]++;
        }
        set<int> free;
        for(int i = min(k, sz); i < sz; ++i) {
            int arv = arrival[i], ld = load[i];
            while(!busy.empty() && arv >= busy.top()[0]) {
                free.insert(busy.top()[1]);
                busy.pop();
            }
            if(!free.empty()) {
                auto it = lower_bound(begin(free), end(free), i % k);
                if(it == end(free)) it = begin(free);                       // __impoartant__ 如果最後一個就繞回第一個
                count[*it]++;
                busy.push({arv + ld, *it});
                free.erase(it);
            }
        }
        vector<int> ans;
        int highLoad{};
        for(auto& ref : count) {
            if(ref.second > highLoad) {
                highLoad = ref.second;
                ans.clear();
                ans.push_back(ref.first);
            } else if(ref.second == highLoad)
                ans.push_back(ref.first);
        }
        return ans;
    }
};
