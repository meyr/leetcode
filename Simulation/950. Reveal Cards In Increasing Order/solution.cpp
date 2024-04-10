/*
 *   一開始我是試著找出規律 但是找不到
 *   後來想到把0 ~ n-1 推入queue 模擬(Simulation)取出的順序
 *   就可以知道取到的牌在vector中那裏 可以放入排過序的牌
 *
 *   time  : O(NlogN + N + N) = O(NlogN)
 *   space : O(N + logN + N) = O(N)
 */
class Solution {
public:
    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        int sz = deck.size();
        vector<int> ans(sz);
        sort(begin(deck), end(deck));
        queue<int> q;
        for(int i = 0; i < sz; ++i)
            q.push(i);
        int i = 0;
        while(!q.empty()) {
            ans[q.front()] = deck[i++]; q.pop();
            if(!q.empty()) {
                q.push(q.front());
                q.pop();
            }
        }
        
        return ans;
    }
};
