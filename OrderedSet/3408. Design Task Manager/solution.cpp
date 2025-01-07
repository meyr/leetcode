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
