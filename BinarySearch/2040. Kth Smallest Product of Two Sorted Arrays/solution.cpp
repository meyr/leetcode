/*  ref : https://leetcode.com/problems/kth-smallest-product-of-two-sorted-arrays/solutions/1527753/binary-search-and-two-pointers-by-votrub-qh6s/
 *
 *  time  : O((N1+N2)logM) : M = max val - min val, N1 : size of nums1, N2 : size of nums2
 *  space : O(N)           : p1, p2, n1, n2, p1r, p2r, n1r, n2r
 */

class Solution {
    using ll = long long;
    long long count(vector<int>& n1, vector<int>& n2, long long m) {
        long long cnt = 0;
        for (int i = 0, j = n2.size() - 1; i < n1.size(); ++i) {
            while (j >= 0 && (long long)n1[i] * n2[j] > m)
                --j;
            cnt += j + 1;
        }
        return cnt;
    }
    /*
        case 1 : 兩個都是整數
            [1, 2, 3, 4]   [2, 3, 4, 5]   binary search 從中間值(nums1最小 * num2最大)開始找target
             i                       j

            iterator每個i, 找出nums1[i] * nums2[j] <= m 的j值，則這個j以下都是符合，所以 cnt += j + 1
            j 不需要重來，因為 i 前進後只會更大，所以只需要繼續往下找就可以

        case 2 : 兩個都是負數
            [-1, -2, -3, -4]  [-2, -3, -4, -5]                                      reverse之後才會滿足j往下數值也變小
              i                             j         n1[i] * n2[j] =  5, 4, 3, 2
                  i                         j         n1[i] * n2[j] = 10, 8, 6, 4
                      i                     j         n1[i] * n2[j] = 15,12, 9, 6

        case 3 : 一正一負
           n [-4, -3, -2, -1]  [1, 2, 3, 4] p
               i                         j            n1[i] * n2[j] = -16, -12, -8, -4 越來越大 (不滿足)

           nr[-1, -2, -3, -4]  [1, 2, 3, 4] p      
               i                         j            n1[i] * n2[j] = -4, -3, -2, -1 越來越小 (滿足) --+   數值變小(不滿足)
                   i                     j            n1[i] * n2[j] = -8, -6, -4, -2 越來越小 (滿足) <-+  

            n [-4, -3, -2, -1]  [4, 3, 2, 1] pr
                i                          j            n1[i] * n2[j] = -4, -8, -12, -16 越來越小 (滿足) ---+  數值變大(滿足)
                    i                      j            n1[i] * n2[j] = -3, -6,  -9, -12 越來越小 (滿足) <--+     
   
    */
public:
    long long kthSmallestProduct(vector<int>& nums1, vector<int>& nums2, long long k) {
        auto it1 = lower_bound(begin(nums1), end(nums1), 0), it2 = lower_bound(begin(nums2), end(nums2), 0);
        vector<int> n1 = vector<int>(begin(nums1), it1), n2 = vector<int>(begin(nums2), it2);
        vector<int> p1 = vector<int>(it1, end(nums1)), p2 = vector<int>(it2, end(nums2));
        vector<int> n1r = vector<int>(rbegin(n1), rend(n1)), n2r = vector<int>(rbegin(n2), rend(n2));
        vector<int> p1r = vector<int>(rbegin(p1), rend(p1)), p2r = vector<int>(rbegin(p2), rend(p2));
        long long left  = min({(ll)nums1.front() * nums2.front(),
                               (ll)nums1.front() * nums2.back(),
                               (ll)nums1.back()  * nums2.front(),
                               (ll)nums1.back()  * nums2.back()  });
        long long right = max({(ll)nums1.front() * nums2.front(),
                               (ll)nums1.front() * nums2.back(),
                               (ll)nums1.back()  * nums2.front(),
                               (ll)nums1.back()  * nums2.back()  });

        while(left < right) {
            long long mid = left + (right - left) / 2;
            long long cnt{};
            if(mid >= 0)
                cnt = count(p1, p2, mid) + count(n1r, n2r, mid) + n1.size() * p2.size() + p1.size() * n2.size();
            else
                cnt = count(n1, p2r, mid) + count(p1r, n2, mid);
            if(cnt >= k) right = mid;
            else left = mid + 1;
        }
        return left;
    }
};
/*
    為什麼binary search 可以成立，因為當mid = nums[i] * nums[j], cnt剛好會在變化的邊界

    mid :  1, 2, 3, 4,  5, 6, 7
    cnt :  0, 0, 1, 1, [2], 2, 2
                    <   >=
*/
