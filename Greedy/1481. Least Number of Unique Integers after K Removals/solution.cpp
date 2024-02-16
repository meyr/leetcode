/* 2024/02/16 daily challenge
   Greedy point : 因為要留下最少的unique number
                  所以從個數最少的num開始刪除		
*/

class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
		// special case
		if(k >= arr.size()) return 0;
        unordered_map<int, int> m;
        for(auto& n : arr) m[n]++; //O(N)
        int ans = m.size();
        map<int, int> freq;
        for(auto& ref : m) freq[ref.second]++; // O(NlogN)
        for(auto it = freq.begin(); it != freq.end() && k > 0; ++it) { // O(N)
            int cnt = min(k / it->first, it->second);
            k -= it->first * it->second;
            ans -= cnt;
        }
        return ans;
	
		// time  : O(N + NlogN + N) = O(NlogN)
		// space : O(N)
    }
};
