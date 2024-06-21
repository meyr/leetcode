/*
 *  使用slinding window找出window中 grumpy[i] == 1時 customers[i]的合為最大值
 *
 *  time  : O(N)
 *  space : O(1)
 */

class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int total{},  sz = grumpy.size();
        for(int i = 0; i < sz; ++i)
            total += grumpy[i] == 0 ? customers[i] : 0;
        if(minutes == 0) return total;
        int ans{};
        for(int left = 0, right = 0; right < sz; ++right) {
            total += grumpy[right] == 1 ? customers[right] : 0;
            if(right >= minutes) {
                total -= grumpy[left] == 1 ? customers[left] : 0;
                left++;
            }
            
            ans = max(ans, total);
        }
        return ans;
    }
};
/*
    1, 0, 1, 2, 1, 1, 7, 5
    0, 1, 0, 1, 0, 1, 0, 1
    
    1     1     1     7     -> minutes = 0, total = 10
    --------
       --------
          --------
*/

// 因為grumpy[i] = 0 or 1所以可以使用multiply
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int total{},  sz = grumpy.size();
        for(int i = 0; i < sz; ++i)
            total += !grumpy[i] * customers[i];
        if(minutes == 0) return total;
        int ans{};
        for(int left = 0, right = 0; right < sz; ++right) {
            total += grumpy[right] * customers[right];
            if(right >= minutes) total -= grumpy[left] * customers[left++];
            ans = max(ans, total);
        }
        return ans;
    }
};
// 最後兩個for loop可以合併成一個
// total 計算原本grumpy[i] == 0 的情況
// added 計算grumpy[i] == 1時的slinding window中的值
class Solution {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int total{},  sz = grumpy.size(), added{}, max_added{};
        for(int left = 0, right = 0; right < sz; ++right) {
            total += !grumpy[right] * customers[right];
            added += grumpy[right] * customers[right];
            if(right >= minutes) added -= grumpy[left] * customers[left++];
            max_added = max(max_added, added);
        }
        return total + max_added;
    }
};
