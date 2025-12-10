/*  上次面試遇到這題 我亂寫
 *
 *  對這類題目還蠻苦手的
 *  使用兩個stack分別記錄string和num
 *
 *
 */
class Solution {
public:
    string decodeString(string s) {
        string res = "";    // 目前這一層的string
        int num = 0;        // 目前這一層的repeat number

        stack <int> nums;       // 紀錄上一層的repeat number
        stack <string> strs;    // 紀錄上一層的string

        int len = s.size();
        for(int i = 0; i < len; ++ i)
        {
            char& c = s[i];
            if(isdigit(c)) num = num * 10 + (c - '0');
            else if(isalpha(c)) res = res + s[i];
            else if(s[i] == '[') {  // 記錄起來, 所以目前的string 和 repeat number都歸零 
                nums.push(num);
                strs.push(res); 
                num = 0;
                res = "";
            } else {                        // 這一層的結尾 表示 xxx[...] 前面有repeat number
                int times = nums.top();
                while(times--)
                    strs.top() += res;      // 把重複的次數記錄在上一層string
                res = strs.top();           // 把上一層的結果load到目前的
                nums.pop();
                strs.pop();
            }
        }
        return res;
    }
};
