/*
 *  題目是要求subarray sum最大值，而且永許你可以刪除一個或是不刪除subarray中的一個element
 *
 *  case 1. 如果不刪除就是一般的subarray問題 可以使用prefix sum來解決
 *  case 2. 刪除一個element的情況就是bwd[i - 1] + fwd[i + 1] 
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    int maximumSum(vector<int>& arr) {
        int sz = arr.size(), ans{INT_MIN};
        vector<int> bwd(sz), fwd(sz);
        {								// 不刪除任何element的subarray sum maximum 
										// 或是刪除前後一個elemet的subarray sum
            int pfs{}, minv{};
            for(int i = 0; i < sz; ++i) {
                pfs += arr[i]; 
                bwd[i] = pfs - minv; 
                minv = min(minv, pfs);
                ans = max(ans, bwd[i]); 
            }
        }
        {
            int pfs{}, minv{};
            for(int i = sz - 1; i >= 0; --i) {
                pfs += arr[i]; 
                fwd[i] = pfs - minv; 
                minv = min(minv, pfs);
            }
        }
        for(int i = 1; i < sz - 1; ++i) // 刪除中間一個element subarra length >= 3
            ans = max(ans, bwd[i - 1] + fwd[i + 1]);
        return ans;
    }
};
