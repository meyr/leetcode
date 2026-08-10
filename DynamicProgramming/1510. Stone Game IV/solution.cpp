/*
 *  time  : O(2N) = O(N)
 *  space : O(2N) = O(N)
 */
class Solution {
    enum player{bob, alice};
    bool helper(int n, int player) {
        if(~mem[n][player]) return mem[n][player];
        for(int i = 1; i * i <= n; ++i) {
            if(helper(n - i * i, !player) == player) // 換別人玩結果還是我贏 那我就選這個
                return mem[n][player] = player;
        }
        return mem[n][player] = !player;    // 試過所有組合都不能贏，那就是對方贏
    }
    vector<vector<int>> mem;
public:
    bool winnerSquareGame(int n) {
        mem.resize(n + 1, vector<int>(2, -1));
        for(int i = 1; i * i <= n; ++i) {
            mem[i * i][0] = 0;
            mem[i * i][1] = 1;
        }
        return helper(n, alice);
    }
};
/*          player
    1 :      alice  true
             bob    false
    2 :      alice  false
             bob    true
    3 :      alice  true
             bob    false

*/
