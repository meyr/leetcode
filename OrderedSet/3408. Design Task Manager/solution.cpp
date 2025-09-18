class TaskManager {
    set<vector<int>> sv;    // 會從vector<int>的第一個element開始排序
    unordered_map<int, set<vector<int>>::iterator> mit;
public:
    // O(NlogN)
    TaskManager(vector<vector<int>>& tasks) {
        for(auto& task : tasks) {
            auto [it, _] = sv.insert({task[2], task[1], task[0]});  // priority先排序 如果priority一樣就根據taskId排序
            mit[task[1]] = it;
        }
    }
    
    // O(logN)
    void add(int userId, int taskId, int priority) {
        auto [it, _] = sv.insert({priority, taskId, userId});   // insert回傳 pair<it, bool>
        mit[taskId] = it;
    }
    
    // O(logN)
    void edit(int taskId, int newPriority) {    // 不能直接改set<vector<int>>裡面的值 所以先刪除再新增
        int userId = (*mit[taskId])[2];
        rmv(taskId);
        add(userId, taskId, newPriority);
    }
    
    // O(logN)
    void rmv(int taskId) {      
        sv.erase(mit[taskId]);
        mit.erase(taskId);
    }
    
    // O(logN)
    int execTop() {
        if(sv.size() == 0) return -1;
        vector<int> last = *sv.rbegin();
        int rtn = last[2];
        sv.erase(last);                     // 不能使用 sv.erase(it) 來刪除 
        return rtn;
    }
};
/*  2025/09/18 daily challenge
 *  
 *  因為execTop會先找priority最高的先執行 如果priority一樣就拿taskId最高的來執行
 *  所以我使用一個map<int, set<int>> 先對priority排序 再用 set<int> 對task排序
 *  另外我只存了taskid 所以需要unordered_map<int, int> 從taskId對應userId和priority
 *
 *  因為 priority, taskId 都是取最大的也可以用set<pair<int, int>> 向上面解答那樣
 *  space : O(N + N + N) = O(N)
 */
class TaskManager {
    unordered_map<int, int> t2u, t2p; // task id to user id, task id to priority
    map<int, set<int>> lists; // priority, taskid
public:
    // O(NlogN)
    TaskManager(vector<vector<int>>& tasks) {
        for(const auto& task : tasks) {
            int u = task[0], t = task[1], p = task[2];
            add(u, t, p);
        }
    }

    // O(logN)
    void add(int userId, int taskId, int priority) {
        t2u[taskId] = userId;
        t2p[taskId] = priority;
        lists[priority].insert(taskId);
    }

    // O(logN + logN) = O(logN)
    void edit(int taskId, int newPriority) {
        int u = t2u[taskId];
        rmv(taskId);
        add(u, taskId, newPriority);
    }

    // O(logN + logN) = O(logN)
    void rmv(int taskId) {
        int p = t2p[taskId];
        lists[p].erase(taskId);
        if(lists[p].empty())
            lists.erase(p);
        t2p.erase(taskId);
        t2u.erase(taskId);
    }

    // O(logN)
    int execTop() {
        int rtn{-1};
        if(!lists.empty()) {
            auto& sp = lists.rbegin()->second;
            int t = *sp.rbegin();
            rtn = t2u[t];
            rmv(t);
        }
        return rtn;
    }
};
