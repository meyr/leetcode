class Solution {
public:
    int findMinimumTime(vector<vector<int>>& tasks) {
        // 使用end排序
        sort(tasks.begin(), tasks.end(), [](const auto& a, const auto& b){
            return a[1] < b[1];
        });
        vector<int> num(2001);
        for(auto& t : tasks) {
            int start = t[0], end = t[1], duration = t[2];
            // 先用別人已經在跑的時間跑
            duration -= count(num.begin() + start, num.begin() + end + 1, 1);
            // 從最後開始填，因為這樣重複地方最多(因為使用end排序)
            for(int i = end; duration > 0; --i) {
                if(num[i] == 0) {
                    duration--;
                    num[i] = 1;
                }
            }
        }
        return count(num.begin(), num.end(), 1);
    }
};
