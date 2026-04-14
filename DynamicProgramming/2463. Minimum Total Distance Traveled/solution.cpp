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
/*  2026/04/14 daily challenge
 *  再寫一次還是沒想到解答
 *  參考上面的答案
 *
 *  + 每個工廠固定修理某個區間的robot
 *
 */
class Solution {
    // 第r個robot, 第f個facotry
    // k : 目前的factory修理了k個robot
    enum status{
        position,
        limit
    };
    using ll = long long;
    ll helper(const vector<int>& robot, const vector<vector<int>>& factory, int r, int f, int k) {
        if(r == robot.size()) return 0; // 全部修完了
        if(f == factory.size()) return 1e13; // 沒修完工廠就用完了
        else if(~mem[r][f][k]) return mem[r][f][k];
        ll goToNextFacotry = helper(robot, factory, r, f + 1, 0);  // 跳下一個工廠
        ll fixThisRobot = k < factory[f][limit] ?                  // 這個工廠是不是還可以修理 如果是就修理此機器人
            abs(robot[r] - factory[f][position]) + helper(robot, factory, r + 1, f, k + 1) : 1e13;
        return mem[r][f][k] = min(goToNextFacotry, fixThisRobot);
    }
    vector<vector<vector<ll>>> mem;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(begin(robot), end(robot));
        sort(begin(factory), end(factory));
        int n = robot.size(), m = factory.size();
        mem.resize(n, vector<vector<ll>>(m, vector<ll>(n, -1)));
        return helper(robot, factory, 0, 0, 0);
    }
};
/*  同上 不需要使用k 一個工廠的可能是 不修理, 修理1台,...修理k台
 *  但是time complexity一樣是O(NMN)
 */
class Solution {
    enum {
        position,
        limit
    };
    using ll = long long;
    ll helper(const vector<int>& robot, const vector<vector<int>>& factory, int r, int f) {
        if(r == robot.size()) return 0;
        if(f == factory.size()) return 1e13;
        else if(~mem[r][f]) return mem[r][f];
        ll rtn = helper(robot, factory, r, f + 1);
        ll sum{};
        for(int k = 1; k <= min(factory[f][limit], (int)robot.size() - r); ++k) {
            sum += abs(robot[r + k - 1] - factory[f][position]);
            rtn = min(rtn, sum + helper(robot, factory, r + k, f + 1));
        }
        return mem[r][f] = rtn;
    }
    vector<vector<ll>> mem;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(begin(robot), end(robot));
        sort(begin(factory), end(factory));
        int n = robot.size(), m = factory.size();
        mem.resize(n, vector<ll>(m, -1));
        return helper(robot, factory, 0, 0);
    }
};
/*  這題讓人思考何謂正確答案?
 *
 *  正確答案就是你嘗試過所有的可能之後 在這些可能的答案裡面挑選一個 符合你條件的答案
 *  因為所有可能的組合你都嘗試過了 所以一定是正確答案
 *
 *  那什麼是所有可能的組合?
 *
 *  對這題來說就是 每個工廠都有可能對每個機器人修理  <-- 如果這樣列舉可能的答案會大的可怕
 *                 因為是要求最小值 所以每個工廠會對連續機器人修理 <-- [0, k] 個連續的機器人修理
 *
 */
