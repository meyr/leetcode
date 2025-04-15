/*  good triplets的定義是 三個數字 在nums1的位置要是遞增 且 此三個數字在nums2的位置也是遞增
 *  例如: x, y, z
 *  
 *       p1x < p1y < p1z and p2x < p2y < p2z
 *
 *  nums1 = [2,0,1,3], nums2 = [0,1,2,3]
 *               *                         從nums1在數字0的位置 往左看有兩個數字 2, 0 這兩個在nums2中只有1位置小於0
 *        
 *  所以使用vector<int> left, right來記錄每個位置往左右看分別有多少個數字滿足
 *  結果就是 ans += left[i] * right[i]
 */

/*  第一個解答使用set來儲存經過的nums在nums2的位置
 *  並且用upper_bound來找多少個滿足的數字
 *
 *  結果TLE
 *
 */
class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int sz = nums1.size();
        unordered_map<int, int> m2; // value to index
        for(int i = 0; i < sz; ++i)
            m2[nums2[i]] = i;
        set<int> s;
        vector<int> left(sz);
        s.insert(m2[nums1[0]]);
        for(int i = 1; i < sz; ++i) {
            left[i] = distance(s.begin(), s.upper_bound(m2[nums1[i]]));
            s.insert(m2[nums1[i]]);
        }
        s.clear();
        vector<int> right(sz);
        s.insert(m2[nums1[sz - 1]]);
        long long ans{};
        for(int i = sz - 2; i >= 0; --i) {
            right[i] = distance(s.upper_bound(m2[nums1[i]]), s.end());
            ans += left[i] * right[i];
            s.insert(m2[nums1[i]]);
        }

        return ans;
    }
};
/*  因為數前後有多少個數字可以用BIT
 *  改寫成BIT就過了 但是我覺得time complexity是一樣的
 */
class BIT{
    vector<int> data;
    int sz;
public:
    BIT(int sz) : data(sz + 2), sz(sz) {}
    void update(int idx, int val) {
        ++idx;
        while(idx <= sz) {
            data[idx] += val;
            idx += idx & -idx;
        }
    }
    int getSum(int idx) {
        ++idx; // 轉換成在BIT中使用的index
        int sum = 0;
        while(idx > 0) {// 因為index 0為dummy node
            sum += data[idx];
            idx -= idx & -idx; // 往parent移動，每次都減掉left most set bit
        }
        return sum;
    }
    void clear() {
        for(int i = 0; i <= sz; ++i)
            data[i] = 0;
    }
};
class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int sz = nums1.size();
        unordered_map<int, int> m2; // value to index
        for(int i = 0; i < sz; ++i)
            m2[nums2[i]] = i;
        BIT bit(1e5);
        vector<int> left(sz);
        bit.update(m2[nums1[0]], 1);
        for(int i = 1; i < sz; ++i) { // O(N(logN + logN)) = O(NlogN)
            left[i] = bit.getSum(m2[nums1[i]]);
            bit.update(m2[nums1[i]], 1);
        }
        bit.clear();
        bit.update(m2[nums1[sz - 1]], 1);
        long long ans{};
        for(int i = sz - 2; i >= 0; --i) {
            long long right = bit.getSum(1e5) - bit.getSum(m2[nums1[i]]);
            ans += left[i] * right;
            bit.update(m2[nums1[i]], 1);
        }

        return ans;
    }
};
