/*   這題的重點是如何有效率地找出 baskets >= fruit且index是最小的
 *
 *   使用vector<vector<int>> 來儲存{basket[i], i} 
 *   1. 先用binary search找出 basket[i] >= fruit
 *   2. 再往後找最小的index
 *
 *   想當然而就是TLE 因為 time complexity : O(N + logN + N(logN + N))) = O(N^2)
 */
class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int ans{};
        vector<vector<int>> bks;
        for(int i = 0; i < baskets.size(); ++i)
            bks.push_back({baskets[i], i});
        sort(begin(bks), end(bks));
        for(const auto& f : fruits) {
            vector<int> target{f, 0};
            auto it = lower_bound(begin(bks), end(bks), target);
            if(it != end(bks)) {
                for(auto cur = next(it); cur != end(bks); ++cur)
                    if((*cur)[1] < (*it)[1])
                        it = cur;
                bks.erase(it);
            } else ans++;
        }
        return ans;
    }
};
/*  步驟二可以使用segment tree來優化
 *  但是這邊參考了另一種解法 : https://leetcode.com/problems/fruits-into-baskets-iii/solutions/7048492/easiest-solution-using-square-root-decomposition-o-n-n/?envType=daily-question&envId=2025-08-06
 *
 *  1. 把 basket 分群 大小為 floor(sqrt(basket.size()))
 *  2. 分別統計每個block的最大值
 *  3. 尋找的時候先找每個block的最大值 
 *  4. 再跳到block內尋找每個element
 *  5. 找到後把element設為0 再跟新此block的最大值
 *
 *  time  : O(N + Nsqrt(N)) = O(Nsqrt(N))
 *  space : O(N + sqrt(N))  = O(N)
 */
class Solution {
    class SRD{
        vector<int> vec, maxv;
        int sz, root;
        void update_maxv_in_region(int r) {
            maxv[r] = 0;
            for(int i = r * root; i < min((r + 1) * root, sz); ++i) {
                maxv[r] = max(maxv[r], vec[i]);
            }
        }
    public:
        SRD(vector<int> _vec) : vec(_vec){
            sz = vec.size();
            root = floor(sqrt(sz));                     // step 1
            maxv.resize(root + 2);
            for(int r = 0; r < maxv.size(); ++r)        // step 2
                update_maxv_in_region(r);
        }
        bool found(int val) {
            int r = maxv.size();
            int idx = -1;
            for(int i = 0; i < maxv.size(); ++i)        // step 3
                if(maxv[i] >= val) {
                    idx = i;
                    break;
                }
            if(idx == -1) return false; // not found
            for(int i = idx * root; i < min((idx + 1) * root, sz); ++i) {   // step 4
                if(vec[i] >= val) {
                    vec[i] = 0;                                             // step 5
                    break;
                }
            }
            update_maxv_in_region(idx);                                     // sep 6
            return true;
        }
    };
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        SRD srd(baskets);
        int ans = fruits.size();
        for(const auto& f : fruits)
            if(srd.found(f))
                ans--;
        return ans;
    }
};
