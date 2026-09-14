/*
 *      參考解答:
 *      圖形可以上下左右移動, 求最大重疊面積.
 *      一開始的想法是移動圖形,但是這樣工程浩大
 *      參考解答,如果圖形任意移動後還是重疊意思是 每個1在img1的位置和 每個1在img2的位置的offset是一樣的
 *      所以可以根據統計 兩個1的位置差來計算最大重疊面積
 *
 *      time  : O(N^2)
 *      sapce : O(N)
 */
class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int sz = img1.size();
        vector<int> la, lb;
        for(int i = 0; i < sz; ++i) for(int j = 0; j < sz; ++j) {
            if(img1[i][j]) la.push_back(i * 1024 + j);
            if(img2[i][j]) lb.push_back(i * 1024 + j);
        }
        int ans{};
        unordered_map<int, int> ump;
        for(int a : la) for(int b : lb) {
            ump[a - b]++;
            ans = max(ans, ump[a - b]);
        }
        return ans;
    }
};
