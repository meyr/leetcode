/*
    先把石頭往右邊集中直到碰到障礙物或是邊界    
    最後旋轉矩陣

*/
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int m = box.size(), n = box[0].size();
        vector<vector<char>> ans(n, vector<char>(m));
        // fall down
        for(int y = 0; y < m; ++y) {
            int cnt = 0;
            box[y].push_back('*');
            for(int x = 0; x < box[y].size(); ++x) {
                if(box[y][x] == '*') {
                    int i = x - 1;
                    while(i >= 0 && cnt) {
                        box[y][i] = '#';
                        cnt--;
                        i--;
                    }
                } else if(box[y][x] == '#') {
                    cnt++;
                    box[y][x] = '.';
                }
            }
            box[y].pop_back();
        }
        // rotate
        for(int y = 0; y < m; ++y) {
            for(int x = 0; x < n; ++x) {
                ans[x][m - y - 1] = box[y][x];
            }
        }
        return ans;
    }
};
