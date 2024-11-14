/*
 *  minimum-maximum問題使用binary search
 *  因為商品只能分配到一間store 且需要全部分配完
 *  所以假設最大是mid 把每個商品分出去 可以分到stores家
 *
 *   ans   1, 2, 3, 4, 5
 *   dist  x  x  x  o  o
 *               >  <=
 *
 *  time  : O(NlogM) ,  N : size of qt, M : search range
 *  space : O(1)
 */
class Solution {
public:
    int minimizedMaximum(int n, vector<int>& qt) {
        if(n == qt.size()) return *max_element(begin(qt), end(qt));
        int left = 1, right = 1e5;
        while(left < right) {
            int mid = left + (right - left) / 2;
            int stores{};
            for(int i = 0; i < qt.size(); ++i)
                stores += (qt[i] + mid - 1)/ mid;
            if(stores > n) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};
/*
*/
