/*
 *  這題的重點是判斷Prime
 *  一開始我是使用第一種方法
 *  參考解答後使用第二種方法
 *
 */
class Solution {
    unordered_map<int, bool> m{{1, false}};
    bool isPrime(int n) {
        if(m.count(n)) return m[n];
        else {
            bool rtn{true};
            for(int i = 2; i <= sqrt(n); ++i)
                if(n % i == 0) {
                    rtn = false;
                    break;
                }
            return m[n] = rtn;
        }
    }
public:
    int maximumPrimeDifference(vector<int>& nums) {
        int i = 0, j = nums.size() - 1;
        while(i < nums.size() && !isPrime(nums[i])) ++i;
        while(i < j && !isPrime(nums[j])) --j;
        return j - i;
    }
};

class Solution {
public:
    int maximumPrimeDifference(vector<int>& nums) {
        vector<int> p(101, 1); //is prime?
        p[0] = p[1] = 0;
        for(int i = 2; i * 2 < 101; ++i) {
            if(!p[i]) continue;
            for(int j = 2; i * j < 101; ++j)
                p[i * j] = 0;
        }
        int i = 0, j = nums.size() - 1;
        while(i < nums.size() && !p[nums[i]]) ++i;
        while(i < j && !p[nums[j]]) --j;
        return j - i;
    }
};
