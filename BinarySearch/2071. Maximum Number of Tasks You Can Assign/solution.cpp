/*  參考: https://leetcode.com/problems/maximum-number-of-tasks-you-can-assign/solutions/1578590/assign-m-easiest-tasks-by-votrubac-ki10/
 *
 *  Greedy + binary search
 *  Greedy point : 用最強的m個worker去挑戰 m個最簡答的task --> 如果可以達成 表示m這個答案可以達到
 *  binary search: 
 *                   no. of tasks : 0, 1, 2, [3], 4, 5, 6    則答案就是3
 *                   complete     : o  o  o   o  x  x  x
 *
 *  time  : O(logM(MlogM)) : M --> min(tasks.size(), workers.size())
 *  space : O(1)
 */
class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& ws, int pills, int strength) {
        int l = 0, r = min(tasks.size(), ws.size()) + 1;
        sort(begin(tasks), end(tasks));
        sort(begin(ws), end(ws));
        while (l < r) { 
            int m = l + (r - l) / 2, need{};
            multiset<int> ms(end(ws) - m, end(ws)); // 把最強的m個worker叫近來
            for (int i = m - 1; i >= 0; --i) { // 先從最難的task開始  
                auto it = prev(end(ms)); // 拿出目前最強的worker
                if (*it < tasks[i]) {   // 目前的worker無法應付這個task
                    it = ms.lower_bound(tasks[i] - strength); // 尋找更弱的worker + strength看看是否可以對付此task
                    if (it == end(ms) || ++need > pills) // 找不到這樣的worker 或是 藥丸使用量超過
                        break;
                }
                ms.erase(it); // 刪除已使用的worker
            }
            if (ms.empty()) l = m + 1;
            else r = m;
        }
        return l - 1;
    }
};
/*
    怎麼判斷這題是binary search? 

    * 存在一個目標數字(這裡是[最多能指派的任務數])
    * 可能的答案需要有單調性 --> 意思是如果答案是k, 則 <= k 成立, > k 不成立 或是相反


    這類「用 binary search 搜答案」的題目常見於：

    * 最大值最小化 / 最小值最大化（例如分配工作、分配書本、最大化最小距離等）  --> min-max problem

    * 最大可行值 / 最小可行值的問題                                            --> 本問題 最大可以達成的任務

    * 某種資源（時間、金錢、數量）限制下的最大處理量

*/
