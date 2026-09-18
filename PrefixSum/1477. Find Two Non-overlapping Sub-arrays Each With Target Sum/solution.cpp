/*
 *      因為要找兩個subarray直覺就是使用prefix sum找出subarray sum
 *      要找出__兩個__subarray的len和為最小 所以使用了backward和forward技巧
 *      backward就是目前的index後面(index比較小)有沒有滿足此條件的subarray, 且拿出最小length的那一個
 *      forward 就是目前的index前面(index比較大)有沒有滿足此條件的subarray, 且拿出最校length的那一個
 *      所以是 ans = min(ans, backward[i] + forward[i + 1])
 *
 *      time  : O(N)
 *      space : O(N)
 *
 */
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int sz = arr.size();
        vector<int> backward(sz, sz + 1), forward(sz, sz + 1);
        {
            unordered_map<int, int> mp;
            mp[0] = -1;
            for(int i = 0, sum = 0; i < sz; ++i) {
                sum += arr[i];
                if(mp.count(sum - target))
                    backward[i] = i - mp[sum - target];
                mp[sum] = i;
                if(i > 0) backward[i] = min(backward[i], backward[i - 1]);
            }
        }
        int ans{sz + 1};
        {
            unordered_map<int, int> mp;
            mp[0] = sz;
            for(int i = sz - 1, sum = 0; i >= 0; --i) {
                sum += arr[i];
                if(mp.count(sum - target))
                    forward[i] = mp[sum - target] - i;
                mp[sum] = i;
                if(i < sz - 1) {
                    forward[i] = min(forward[i], forward[i + 1]);
                    ans = min(ans, backward[i] + forward[i + 1]);
                }
            }
        }
        return ans >= sz + 1 ? -1 : ans;
    }
};
/*      參考gemini解法
 *      不需要使用unordered_map因為arr[i] > 0 所以使遞增關係 只需要使用slinding windows(left, right)
 *      另外使用best_len紀錄目前的最小lenght
 *      當找到一個滿足的subarray 就跳到left - 1去看看是否有 best_len[left - 1]
 *
 *      time  : O(N)
 *      space : O(N)
 */
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int sz = arr.size();
        // best_len[i] 代表在 0 到 i 之間，符合條件的子陣列的最小長度
        vector<int> best_len(sz, sz + 1);

        int sum = 0, left = 0, min_so_far = sz + 1, ans = sz + 1;

        // 第一輪：由左向右掃描，並記錄每個位置左側（包含自己）的最短合法子陣列長度
        for (int right = 0; right < sz; ++right) {
            sum += arr[right];
            while (sum > target) {  // windows太大內縮
                sum -= arr[left++];
            }
            if (sum == target) {    // windows sum剛好是target
                int cur_len = right - left + 1;
                if (left > 0) {
                    ans = min(ans, cur_len + best_len[left - 1]);
                }
                min_so_far = min(min_so_far, cur_len);  // 目前看到最小的length
            }
            best_len[right] = min_so_far;
        }

        return ans > sz ? -1 : ans;
    }
};
