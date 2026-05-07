/*  參考 : https://leetcode.com/problems/jump-game-ix/solutions/8133882/jump-game-ix-by-leetcode-9mtu/
 *
 *  往左跳可以數值越跳越大，往右跳只會越跳越小，但是題目是要可以跳到的最大值 所以盡可能的往左跳
 *
 *  5, 4, 3, 7, 3, 2
 *     |__|__  對4, 3來說往左跳最大就是 5
 *
 *              |__|_> 對 3, 2來說雖然可以跳到4, 5, 但是我要最大值 所以跳到7就好
 *
 *  於是我們使用一個stack 來記錄 5, 7 ... 遞增數值 因為在他中間的值只會跳到左邊的最大值
 *
 */
class Solution {
    struct Item{        // 紀錄每個區間[left, right] 和中間的最大值
        int value;
        int left;
        int right;
        Item(int val, int idx) : value(val), left(idx), right(idx) {}
    };
public:
    vector<int> maxValue(vector<int>& nums) {
        vector<Item> st;
        for(int i = 0; i < nums.size(); ++i) {
            Item cur(nums[i], i);
            while(!st.empty() && st.back().value > nums[i]) { // 遇到比自己小的nums[i]就合併到目前的區域 因為只能跳到st.back().value
                auto& top = st.back();
                cur.value = max(top.value, cur.value);
                cur.left = top.left;
                st.pop_back();
            }
            st.push_back(cur); // 如果是新的最高點 就保存起來
        }
        for(auto& ref : st)
            for(int i = ref.left; i <= ref.right; ++i)
                nums[i] = ref.value;
        return nums;
    }
};
