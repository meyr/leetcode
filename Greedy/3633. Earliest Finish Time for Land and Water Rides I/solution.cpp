/*  暴力破解
 *  窮舉所有的可能 先land後water 和 先water後land
 *
 *  time  : O(NM + NM) = O(NM) 因為 n, m <= 100 所以可以過
 */
class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int ans = 1e6;
        // first land then water
        for(int i = 0; i < landStartTime.size(); ++i)
            for(int j = 0; j < waterStartTime.size(); ++j)
                if(landStartTime[i] + landDuration[i] >= waterStartTime[j])
                    ans = min(ans, landStartTime[i] + landDuration[i] + waterDuration[j]);
                else
                    ans = min(ans, waterStartTime[j] + waterDuration[j]);

        // first water then land
        for(int i = 0; i < waterStartTime.size(); ++i)
            for(int j = 0; j < landStartTime.size(); ++j)
                if(waterStartTime[i] + waterDuration[i] >= landStartTime[j])
                    ans = min(ans, waterStartTime[i] + waterDuration[i] + landDuration[j]);
                else
                    ans = min(ans, landStartTime[j] + landDuration[j]);
        return  ans;
    }
};
/*  參考 : https://leetcode.com/problems/earliest-finish-time-for-land-and-water-rides-i/solutions/7036578/javacpython-straight-forward-solution-by-7z3m/
 *
 *  Greedy point : 1. 先參加最先結束的land ride再看可以參加哪一個water ride可以最早結束
 *                 2. 反過來 先參加最早結束的water ride再看可以參加哪一個land ride
 *
 *  找到先結束的ride後
 *        |--------------|
 *                     land
 *    |---------|                 case1
 *           |----------------|   case1
 *                          |------------|   case2
 *
 *  case1: startTime <= land  --> 要等land結束後才可以加入 所以是 land + waterDuration
 *  case2: startTime  > land  --> 要等此water ride結束  waterStartTime + waterDuration
 *                                                                 /|\
 *                                                                  |____ 只有前面這一項不一樣 是根據誰比較大就採用誰 所以是max(land, waterStartTime)
 *
 *  time  : O(N + M)  不用排序避免NlogN和MlogM
 *  space : O(1)
 */
class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size(), m = waterStartTime.size(), land = 1e9, water = 1e9, land_water = 1e9, water_land = 1e9;
        for (int i = 0; i < n; ++i)
            land = min(land, landStartTime[i] + landDuration[i]);   // 找出最先結束的land ride

        for (int i = 0; i < m; ++i) {
            water = min(water, waterStartTime[i] + waterDuration[i]); // 找出最先結束的water ride
            land_water = min(land_water, max(waterStartTime[i], land) + waterDuration[i]); // __impoartant__
        }

        for (int i = 0; i < n; ++i)
            water_land = min(water_land, max(landStartTime[i], water) + landDuration[i]);

        return min(water_land, land_water);
    }
};
