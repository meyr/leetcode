/*  把nums都放進unordered_set<string>中
 *  然後從0開始找沒出現過的value
 *
 */
class Solution {
public:
    string findDifferentBinaryString(vector<string>& nums) {
        unordered_set<string> us(begin(nums), end(nums));
        int sz = nums.front().size();
        string ans = string(sz, '0');
        int idx{};
        while(us.count(ans)) {
            if(ans[sz - idx - 1] == '1') {
                ans[sz - idx - 1] = '0';
                idx++;
            }
            ans[sz - idx - 1] = '1';
        }
        return ans;
    }
};
/* 
 * 以下均參考此解答 : 
 * https://leetcode.com/problems/find-unique-binary-string/solutions/1418743/sweep-omg-and-randomization-by-votrubac-mtab/
 *
 */
/*
 *  一樣的概念 把string先轉乘int再轉回來
 */
string findDifferentBinaryString(vector<string>& nums) {
    unordered_set<int> m;
    for (auto &n : nums)
        m.insert(stoi(n, nullptr, 2));  // __important__ binary string to int
    for (int x = 0; ; ++x)
        if (!m.count(x))
            return bitset<16>(x).to_string().substr(16 - nums.size());  // __important__ 因為bitset不能給變數當參數 所以先給16再截斷成要的大小
    return "";
}
/*
 *  因為只要找到不一樣的binary string, 只需要找出一個string和每個nums[i]都有一個bit不一樣
 *
 */
string findDifferentBinaryString(vector<string>& nums) {
    for (int i = 0; i < nums.size(); ++i)
        nums[0][i] = nums[i][i] == '0' ? '1' : '0';  // __important__ 答案放在nums[0], 每個nums[i]和nums[0] 第i個bit不一樣
    return nums[0];
}
/*  
 *  因為size = N的binary string總共有2^N個情況, 但是題目只給size = N 的vector<string> nums
 *  所以隨便選一個都有可能是解答
 */
string findDifferentBinaryString(vector<string>& nums) {
    string res(nums.size(), '0');
    while (any_of(begin(nums), end(nums), [&res](const auto &num){ return num == res; })) // nums中任何一個element 滿足res == num就繼續
        generate(begin(res), end(res),  [](){ return rand() % 2 ? '1' : '0'; });          // 產生一個random binary string
    return res;
}
