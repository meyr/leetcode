/*
 *  題目提到  minimum magnetic force between any two balls is maximum
 *  min-max題目就想到是binary search
 *
 *  假設可以得到的force如下 則result就是是否可以排列出這樣的force
 *
 *  force  1, 2, 3, 4, 5, 6
 *  result o  o  o  x  x  x
 *  answer       *
 *
 *  time  : O(NlogN + NlogM), N : size of position, M : max position - min position
 *  space : O(logN)
 */ 

class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(begin(position), end(position));
        int left = 1, right = position.back() - position.front();
        if(m == 2) return right;
        while(left < right) {
            int mid = left + (right - left) / 2;
            int prevp = position[0]; // 在最前面放入第一個球
            int k = m - 1;
            for(int i = 1; i < position.size() && k > 0; ++i) {
                if(position[i] - prevp >= mid) {
                    k--;
                    prevp = position[i];
                }
            }
            if(k == 0) left = mid + 1;
            else right = mid;
        }
        return left - 1;
    }
};
/* 2025/02/14 daily challenge
 *
 *  minimum mangetic force between any two balls is maximum -> maximum-minimum problem -> binary search
 *  
 *  minimum magnetic force between any two balls : 1, 2, 3,  4, 5, 6
 *                                    need balls : 5, 5, 4, [4], 3, 2, m = 4 --> take m == 4 and force is maximum
 *                                                           >=  <
 *  time  : O(NlogN + NlogM), N : size of position, M : max position - min position
 *  space : O(logN)
 */
class Solution {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(begin(position), end(position));
        int left = 1, right = position.back() - position.front() + 1;
        while(left < right) {
            int mid = left + (right - left) / 2;
            int cnt{1}, prev = position[0];
            for(int i = 1; i < position.size(); ++i)
                if(position[i] - prev >= mid) {
                    cnt++;
                    prev = position[i];
                }
            if(cnt < m) right = mid;
            else left = mid + 1;

        }
        return left - 1;
    }
};
