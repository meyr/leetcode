/*  使用sort再來數連續的數字有多少個
 *
 *  time  : O(NlogN + N) = O(NlogN) 不符合題意O(N)
 *  space : O(logN)
 */
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int sz = nums.size();
        if(sz <= 1) return sz;
        sort(begin(nums), end(nums));
        int ans{1}, cur{1};
        for(int i = 1; i < nums.size(); ++i) {
            if(nums[i] == nums[i - 1]) continue;
            else if(nums[i] == nums[i - 1] + 1)
                cur++;
            else cur = 1;
            ans = max(ans, cur);
        }
        return ans;
    }
};
/*  使用union find
 *
 *  time  : O(N + N + N + N) = O(N)
 *  space : O(N + N) = O(N)
 */
class Solution {
    vector<int> root, rank;
    int ans{1};
    int find(int x) {
        if(root[x] == x) return x;
        else return root[x] = find(root[x]);
    }
    int un(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return 0;
        if(rank[y] > rank[x]) swap(x, y);
        root[y] = x;
        rank[x] += rank[y];
        ans = max(ans, rank[x]);
        return rank[x];
    }
public:
    int longestConsecutive(vector<int>& nums) {
        int sz = nums.size();
        if(sz <= 1) return sz;
        root.resize(sz);
        iota(begin(root), end(root), 0);
        rank.resize(sz, 1);
        unordered_map<int, int> um; // value, index
        for(int i = 0; i < sz; ++i) {
            if(um.count(nums[i])) continue;
            if(um.count(nums[i] - 1))
                un(i, um[nums[i] - 1]);
            if(um.count(nums[i] + 1))
                un(i, um[nums[i] + 1]);
            um[nums[i]] = i;
        }
        return ans;
    }
};
