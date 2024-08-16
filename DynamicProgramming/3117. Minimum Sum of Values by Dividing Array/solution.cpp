/*  下面是我寫出來的但是TLE
 *
 *  time  : O(NMN) 因為helper裡面有個for loop
 */
class Solution {
    long helper(vector<int>& nums, vector<int>& andValues, int i, int j) {
        if(i == nums.size() && j == andValues.size()) return mem[i][j] = 0;
        else if(i == nums.size() || j == andValues.size()) return mem[i][j] = INT_MAX; 
        else if(~mem[i][j]) return mem[i][j];
        long val{-1}, rtn = INT_MAX;
        for(int k = i; k < nums.size(); ++k) {
            if(nums.size() - k < andValues.size() - j) break;
            val &= nums[k];
            if(val == andValues[j])
                rtn = min(rtn, nums[k] + helper(nums, andValues, k + 1, j + 1));
        }
        return mem[i][j] = rtn;
    }
    vector<vector<long>> mem;
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        mem.resize(nums.size() + 1, vector<long>(andValues.size() + 1, -1));
        long rtn = helper(nums, andValues, 0, 0);
        return rtn >= INT_MAX ? -1 : rtn;
    }
};

/*  參考解答 : https://leetcode.com/problems/minimum-sum-of-values-by-dividing-array/solutions/5019590/c-dp-easy-to-understand/
 *
 *  不使用for loop就必須針對每個element來決定是否納入(take or notake) 
 *  並且多紀錄目前and的結果
 *
 *  time  : O(NMlog(max element))
 *  space : O(NMlog(max element)) 
 */
class Solution {
	public:
	vector<vector<unordered_map<int,int>>> dp;
	int helper(vector<int>& nums, vector<int>& andValues, int i, int j, int And){
        if(i == nums.size() && j == andValues.size()) return 0;
        else if(i == nums.size() || j == andValues.size()) return 1e8;
		else if(dp[i][j].count(And)) return dp[i][j][And];

		int inclu = 1e8;
		if((And & nums[i]) == andValues[j]) {
			inclu = nums[i] + helper(nums, andValues, i+1, j + 1, -1);
		}
		int exclu = helper(nums, andValues, i + 1, j, (And & nums[i]));

		return dp[i][j][And] = min(inclu, exclu);
	}
	int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
		int n = nums.size(), m = andValues.size();
		dp.resize(n + 1, vector<unordered_map<int,int>> (m + 1));
		int ans = helper(nums, andValues, 0, 0, -1);
		if(ans==1e8) return -1;
		return ans;
	}
};

/*
 * 參考leetcode.cn官方解答 : 
 * https://leetcode.cn/problems/minimum-sum-of-values-by-dividing-array/solutions/2877228/hua-fen-shu-zu-de-dao-zui-xiao-de-zhi-zh-dcik/
 *
 * 把i, j 合併成key = i * m + j;
 *
 */
class Solution {
public:
    int minimumValueSum(vector<int>& nums, vector<int>& andValues) {
        int n = nums.size(), m = andValues.size();
        memo.resize(m * n);
        int res = dfs(0, 0, INF, nums, andValues);
        return res < INF ? res : -1;
    }

private:
    static const int INF = (1 << 20) - 1; // all 1, 和-1效果一樣
    vector<unordered_map<int, int>> memo;
    int dfs(int i, int j, int cur, vector<int>& nums, vector<int>& andValues) {
        int n = nums.size(), m = andValues.size(), key = i * m + j;
        if (n - i < m - j) return INF; // 個數不足 
        if (i == n && j == m) return 0;
        if (i == n || j == m) return INF;
        if (memo[key].count(cur)) return memo[key][cur];

        cur &= nums[i];
        if ((cur & andValues[j]) < andValues[j]) return INF; // 因為數值只會更小 所以不可能達到了

        int res = dfs(i + 1, j, cur, nums, andValues);
        if (cur == andValues[j]) {
            res = min(res, dfs(i + 1, j + 1, INF, nums, andValues) + nums[i]);
        }
        memo[key][cur] = res;
        return res;
    }
};

