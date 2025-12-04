/*
 * 一開始以為只要比較兩兩的char就可以 但是少考慮了 RRRRRRL 這樣的情況
 *
 */
class Solution {
    unordered_map<string, int> score{{"LL", 0}, {"LS", 0}, {"LR", 0},
                                     {"SL", 1}, {"SS", 0}, {"SR", 0},
                                     {"RL", 2}, {"RS", 1}, {"RR", 0}};
public:
    int countCollisions(string directions) {
        int ans{};
        string prev = string(1, directions[0]);
        for(int i = 1; i < directions.size(); ++i) {
            prev += directions[i];
            ans += score[prev];
            if(score[prev] == 0) prev = directions[i];
            else prev = 'S';
        }
        return ans;
    }
};
/* 
 * 改使用stack 如果是'S'就要繼續檢查stack是否empty或是為'R'
 *
 */
class Solution {
public:
    int countCollisions(string directions) {
        stack<char> st;
        int ans{};
        for(auto& d : directions) {
            if(d == 'S') {
                while(!st.empty() && st.top() == 'R') {
                    ans++;
                    st.pop();
                }
                st.push(d);
            } else if(d == 'L') {
                if(st.empty()) continue;
                else if(st.top() == 'S') ans++;
                else if(st.top() == 'R') {
                    while(!st.empty() && st.top() == 'R') {
                        ans++;
                        st.pop();
                    }
                    ans++;
                    st.push('S');
                }
            } else st.push(d);
        }
        return ans;
    }
};
/*
 * 因為兩個'S'中間的都會碰撞 所以只要找從左邊開始第一個出現的非'L' 和 從右邊找出第一個出現非'R'
 * 計算這兩個中間的非'S'即可
 */
class Solution {
public:
    int countCollisions(string directions) {
        int sz = directions.size();
        int left = 0, right = sz - 1;
        while(left < sz && directions[left] == 'L') left++;
        while(right >= 0 && directions[right] == 'R') right--;
        if(left < right)
            return count_if(begin(directions) + left, begin(directions) + right + 1, [](auto& c){
                return c != 'S';
            });
        else return 0;
    }
};
