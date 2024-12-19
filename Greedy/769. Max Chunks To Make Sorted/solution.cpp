/*  
 *  使用ed紀錄目前最大值 意味著我們需要收集 st ~ ed這麼多數字 來進行排列
 *
 *   time  : O(N)
 *   space : O(1)
 *
 */
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int ans{}, st{}, ed{}, cnt{};
        for(int i = 0; i < arr.size(); ++i) {
            ed = max(ed, arr[i]);
            if(ed - st + 1 == ++cnt) {
                ans++;
                cnt = 0;
                st = ++ed;
            }
        }
        return ans;
    }
};
