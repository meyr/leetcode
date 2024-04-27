class Solution {
    int sz;
    unordered_map<char, vector<int>> m;
    int helper(int i, string& key, int j) {
        if(~mem[i][j]) return mem[i][j];
        int ans{INT_MAX};
        for(auto& p : m[key[j]]) { // i 移動到 p
            int a = i, b = p;   // b > a
            if(a > b) swap(a, b);
            ans = min(ans, min(b - a, a - b + sz) + 1 + 
			    helper(p, key, j + 1));
        }
        return mem[i][j] = ans;
    }
    vector<vector<int>> mem;
public:
    int findRotateSteps(string ring, string key) {
        sz = ring.size();
        mem.resize(sz, vector<int>(key.size() + 1, -1));
        for(int i = 0; i < sz; ++i) {
            m[ring[i]].push_back(i);
            mem[i][key.size()] = 0;
        }
        return helper(0, key, 0);
    }
};
