/*  使用BFS模擬骨牌效應
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
public:
    string pushDominoes(string dominoes) {
        queue<pair<int, int>> q; // position, direction
        for(int i = 0; i < dominoes.size(); ++i)
            if(dominoes[i] != '.')
                q.push({i, dominoes[i] == 'L' ? -1 : 1});
        while(!q.empty()) {
            unordered_map<int, int> m; // position, direction
            while(!q.empty()) {
                auto [p, d] = q.front(); q.pop();
                m[p + d] += d;
            }
            for(auto& ref : m) {
                if(ref.second != 0 && ref.first >= 0 && ref.first < dominoes.size() && dominoes[ref.first] == '.') {
                    dominoes[ref.first] = ref.second == -1 ? 'L' : 'R';
                    q.push({ref.first, ref.second});
                }
            }
        }   
        return dominoes;     
    }
};

