/*  因為從1開始，每次最多只能加1, 所以最大值只會是sz = arr.size()
 *  先對arr排序然後針對每個位置取最大值，因為題目要求得到最大的elemnet
 *
 *  time  : O(NlogN)
 *  space : O(logN)
 */
 class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int sz = arr.size();
        if(sz == 1) return 1;
        sort(begin(arr), end(arr)); // T: O(NlogN), S: O(logN)
        int cur{1};
        for(int i = 1; i < sz; ++i) // O(N)
            cur += (arr[i] == cur);

        return cur;
    }
};
/*  如果要再優化那就是使用counting sort 但是看到1 <= arr[i] <= 1e9 就放棄了
 *  後來看到官方解答才恍然大悟，因為上面提到最大只會到sz, 所以不需要使用一個1e9的vector來數
 *  對這題來說數超過sz的數值已經沒有意義。
 *  所以使用vector<int> count(sz + 1) 來數就夠了
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    int maximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        int n = arr.size();
        vector<int> counts = vector(n + 1, 0);
        
        for (int num : arr) {
            counts[min(num, n)]++;
        }
        
        int ans = 1;
        for (int num = 2; num <= n; num++) {
            ans = min(ans + counts[num], num);
        }
        
        return ans;
    }
};
