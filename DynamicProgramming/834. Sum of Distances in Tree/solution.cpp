/*
 *   參考答案 : 
 *   https://leetcode.com/problems/sum-of-distances-in-tree/solutions/1308366/c-solution-using-dfs-with-explanation-o-n-time-complexity/
 *
 */

class Solution {
public:
    vector<vector<int>> v;
    vector<int> counter, res;
    // 只會得到node = 0 的正確解答，但是也同時建立了每個node的counter(非parent的child個數)    
    // 因為要得到node = 0 的解答，必須先知道child的解答 所以是post-order
    void dfs(int root, int parent = -1) {
        for(auto child : v[root]) {
            if(child == parent) continue;
            dfs(child, root);
            counter[root] += counter[child]; // 只計算非parent以下的node數目
            res[root] += res[child] + counter[child]; // 只會更新非leaf node
            //          ------------ child到每個node的距離 + 
            //                       ----------------- root到child的距離(也就是個數)
        }
        counter[root] += 1; // 加上自己
    }
    // 已經知道res[root]的答案後，開始推到每個child
    // 因為要得到child的答案，必須先知道root的解答，所以是pre-order
    void dfs2(int root, int n, int parent = -1) {
        for(auto child : v[root]) {
            if(child == parent) continue;
            res[child] = res[root] - counter[child] + n - counter[child];
            //                      --------------- 靠近了counter[child]
            //                                       -------------------- 遠離了n - counter[child]
            dfs2(child, n, root);
        }
    }
    
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        v.resize(n);
        for(int i = 0; i < n - 1; i++) {
            int a = edges[i][0];
            int b = edges[i][1];
            v[a].push_back(b);
            v[b].push_back(a);
        }
        res.resize(n);
        counter.resize(n);
        dfs(0);
        dfs2(0, n);
        return res;
    }
};
