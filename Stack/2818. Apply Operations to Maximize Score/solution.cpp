/*  參考解答
 *  
 */
 // 計算prime score有個prime list會方便很多
 const vector<int> primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
    137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223,
    227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313};
const int MOD = 1e9 + 7;
class Solution {
    // 使用pow mod來降地計算次數
    int powMod(int x, int y, int m) {
        if(y == 0) return 1;
        else if(y == 1) return x;
        else {
            int k = y / 2;              
            long p = powMod(x, k, m);
            long rtn = (p * p) % m;             // 關鍵在把pow拆成兩半 pow(x, y) = pow(x, y/2) * pow(x, y/2) * (y%2 ? x : 1)
            return (rtn * (y % 2 ? x : 1)) % m;
        }
    }
    unordered_map<int, int> mem;
    int primeScore(int n) {
        int rtn{}, val{n};
        if(mem.count(n)) return mem[n];
        for(int i = 0; i < primes.size() && n >= primes[i]; ++i) {
            int p = primes[i];
            if(val % p == 0) {
                rtn++;
                while(val && val % p == 0)
                    val /= p;
            }
        }
        return mem[n] = rtn + (val > 1);
    }
    void print(vector<int>& vecs) {
        for(auto& n : vecs)
            cout << n << ", ";
        cout << endl;
    }
public:
    int maximumScore(vector<int>& nums, int k) {
        int sz = nums.size();
        vector<int> ps;
        for(int i = 0; i < nums.size(); ++i)    // 先找出所有的prime score
            ps.push_back(primeScore(nums[i]));
        vector<int> right(sz, sz);
        stack<int> st;
        for(int i = 0 ; i < sz; ++i) {                      // 向右找出比目前prime socre還大的index
            while(!st.empty() && ps[i] > ps[st.top()]) {    // 如果prime socre相等不影響，繼續往下尋找 
                right[st.top()] = i;                        // 因為題目說會使用index最小的
                st.pop();
            }
            st.push(i);
        }
        st = stack<int>();
        vector<int> left(sz, -1);
        for(int i = sz - 1; i >= 0; --i) {                  // 向左找出比目前prime score 等於或大於的index
            while(!st.empty() && ps[i] >= ps[st.top()]) {   // 因為prime score相等就會取到此num所以只好停止尋找
                left[st.top()] = i; 
                st.pop();
            }
            st.push(i);
        }
        map<int, long> m;// nums[i], count      因為nums[i]可能會相等，所以使用map來記錄每個num[i]有多少組subarray
        for(int i = 0; i < sz; ++i)
            m[nums[i]] += (long)(i - left[i]) * (right[i] - i);
        int rtn{1};
        auto it = m.rbegin();
        while(k && it != m.rend()) {
            int num = it->first;
            long cnt = it->second;
            it++;
            long count = min((long)k, cnt);
            rtn = (rtn * (long)powMod(num, count, MOD)) % MOD;
            k -= count;
        }
        return rtn;
    }
};
