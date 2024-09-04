/*
 * 簡單的想法直接模擬走法
 *
 * time  : O(NlogM), N : sizeof commands, M : sizeof obstacles
 * space : O(M)
 */
class Solution {
    vector<vector<int>> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    struct VectorHasher{ // hash function for vector<int>
        size_t operator()(const vector<int>& v) const{
            hash<int> hasher;
            size_t seed{};
            for(int i : v) seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        };
    };
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int y{}, x{}, d{}, ans{};
        set<vector<int>> obs(begin(obstacles), end(obstacles));
        //unordered_set<vector<int>, VectorHasher> obs(begin(obstacles), end(obstacles));
        for(auto& c : commands) { //O(N)
            if(c == -1) d = (d + 1) % 4;
            else if(c == -2) d = (d + 3) % 4;
            else {
                while(c--) {
                    int ny = y + dirs[d][0], nx = x + dirs[d][1];
                    if(obs.count({ny, nx})) break; // 因為使用set所以time complexity是O(logM) 如果使用unordered_set則是O(1) 
                    else {
                        y = ny;
                        x = nx;
                    } 
                }
            }
            ans = max(ans, y * y + x * x);
        }
        return ans;
    }
};
