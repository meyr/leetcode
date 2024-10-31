/*
    參考:https://leetcode.com/problems/minimum-total-distance-traveled/solutions/2783305/python-dp-solution/

    第i個robot去第j個factory 因為第i個robot都有可能去每個工廠維修 所以必須每個都嘗試
    因為j, k綁定再一起 所以可以使用k來表示第j個工廠的limit

    time  : O(NMN) N:size of robot, M : size of factory
    space : O(NMN)
*/

class Solution {
    // i : robot
    // j : factory
    // k : 總共有幾個robot去了第j個工廠
    long long helper(int i, int j, int k, vector<int>& r, vector<vector<int>>& f) {
        if(i == r.size()) return 0;
        if(j == f.size()) return 1e16;              //沒有工廠可以修理了
        if(~mem[i][j][k]) return mem[i][j][k];
        long long res1 = helper(i, j + 1, 0, r, f); // 第i個robot去第j + 1間工廠, 因為是第一個去j+1工廠 所以k=0
        long long res2 = (k < f[j][1]) ?            // 超過此工廠limit 給出1e16也就是只能去下一間
                        abs(f[j][0] - r[i]) + helper(i + 1, j, k + 1, r, f) : // 在此工廠修理，計算距離k+1
                        1e16;
        return mem[i][j][k] = min(res1, res2);
    }
    vector<vector<vector<long long>>> mem;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(begin(robot), end(robot));
        sort(begin(factory), end(factory));
        mem.resize(robot.size(), vector<vector<long long>>(factory.size(), vector<long long>(robot.size(), -1)));
        return helper(0, 0, 0, robot, factory);
    }
};
