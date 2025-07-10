/* 因為可以移到k個meeting等於是把k個meeting前後的空閒時間加起來
 * 所以先統計每個meeting前後sapce
 * 然後用slinding window找出最大值
 *
 * time  : O(N)
 * space : O(N)
 */

class Solution {
public:
    int maxFreeTime(int eventTime, int k, vector<int>& startTime, vector<int>& endTime) {
        vector<int> space;
        if(startTime.front() > 0) space.push_back(startTime.front());
        for(int i = 1; i < startTime.size(); ++i)
                space.push_back(startTime[i] - endTime[i - 1]);
        if(eventTime > endTime.back())
            space.push_back(eventTime - endTime.back());
        int ans{}, cur{};
        for(int i = 0; i < space.size(); ++i) {
            cur += space[i];
            if(i > k)
                cur -= space[i - k - 1];
            ans = max(ans, cur);
        }
        return ans;
    }
};

/*
    0----------------------------------------------21
               7-----10
                     10----------14
                                      16-------18
*/
