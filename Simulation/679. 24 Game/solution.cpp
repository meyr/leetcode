/*  參考: https://leetcode.com/problems/24-game/solutions/107678/c-concise-code
 *
 *  time  : O(N!)
 *  space : O(N!)
 */
class Solution {
public:
    bool judgePoint24(vector<int>& nums) {
        sort(nums.begin(), nums.end());                             // 先排序得到第一種排列
        do {
            if (valid(nums)) return true;
        } while(next_permutation(nums.begin(), nums.end()));        // __importatn__ 使用next_permutation可以嘗試所有的排列組合
        return false;                                               //               如果不先sort, 則會從目前的pattern開始往下排列 有可能不會列舉所有的排列組合
    }
private:
    bool valid(vector<int>& nums) {                                 // 嘗試所有的可能
        double a = nums[0], b = nums[1], c = nums[2], d = nums[3];
        if(valid(a + b, c, d) || valid(a, b + c, d) || valid(a, b, c + d)) return true;
        if(valid(a - b, c, d) || valid(a, b - c, d) || valid(a, b, c - d)) return true;
        if(valid(a * b, c, d) || valid(a, b * c, d) || valid(a, b, c * d)) return true;
        if(valid(a / b, c, d) || valid(a, b / c, d) || valid(a, b, c / d)) return true;
        return false;
    }
    bool valid(double a, double b, double c) {
        if(valid(a + b, c) || valid(a, b + c)) return true;
        if(valid(a - b, c) || valid(a, b - c)) return true;
        if(valid(a * b, c) || valid(a, b * c)) return true;
        if(b && valid(a / b, c) || c && valid(a, b / c)) return true;       // __important__ 除法必須注意除數不能為0
        return false;
    }
    bool valid(double a, double b) {
        if (abs(a + b - 24.0) < 0.0001 ||
            abs(a - b - 24.0) < 0.0001 ||
            abs(a * b - 24.0) < 0.0001 ||
            b && abs(a / b - 24.0) < 0.0001) return true;
        return false;
    }
};
