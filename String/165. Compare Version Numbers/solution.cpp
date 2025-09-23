/*
 *   使用兩個pointer來對version做parse
 *   必須注意pointer必須往前 否則會卡在'.'
 *
 *   time  : O(N + M)
 *   space : O(1)
 */
class Solution {
public:
    int compareVersion(string version1, string version2) {
        int sz1 = version1.size(), sz2 = version2.size();
        int i = 0, j = 0;
        while(i < sz1 || j < sz2) {
            int val1{}, val2{};
            while(i < sz1 && version1[i] != '.') val1 = val1 * 10 + (version1[i++] - '0');
            while(j < sz2 && version2[j] != '.') val2 = val2 * 10 + (version2[j++] - '0');
            if(val1 > val2) return 1;
            else if(val1 < val2) return -1;
			i++, j++; // __important__否則i和j會停在'.'
        }
        return 0;
    }
};
/*
 *   使用istringstream 來parse 並把結果存進vector在進行比較
 *
 *   time  : O(N + M)
 *   space : O(N + M)
 */
class Solution {
public:
    int compareVersion(string version1, string version2) {
        vector<int> v1, v2;
        istringstream iss1(version1), iss2(version2);
        string str;
        while(getline(iss1, str, '.')) v1.push_back(stoi(str));
        while(getline(iss2, str, '.')) v2.push_back(stoi(str));
        int i = 0, j = 0;
        for(;i < v1.size() && j < v2.size(); ++i, ++j) {
            if(v1[i] > v2[j]) return 1;
            else if(v1[i] < v2[j]) return -1;
        }
        while(i < v1.size() && v1[i] == 0) ++i;
        while(j < v2.size() && v2[j] == 0) ++j;
        if(i == v1.size() && j == v2.size()) return 0;
        else if(i == v1.size()) return -1;
        else return 1;
    }
};
/*  2025/09/23 daily challenge
 *  方法和上面類似 先parse得到vector
 *  然後比較vector內容
 *
 *  time  : O(N + M)
 *  space : O(N + M)
 */
class Solution {
    auto parse(const string& str) -> vector<int> {
        istringstream iss(str);
        string word;
        vector<int> rtn;
        while(getline(iss, word, '.'))
            rtn.push_back(stoi(word));
        return rtn;
    }
public:
    int compareVersion(string version1, string version2) {
        auto ver1 = parse(version1);
        auto ver2 = parse(version2);
        for(auto i = 0; i < max(ver1.size(), ver2.size()); ++i) {
            auto val1 = i < ver1.size() ? ver1[i] : 0;              // __important__ 到底了就是0 這樣就可以一直比下去
            auto val2 = i < ver2.size() ? ver2[i] : 0;
            if(val1 > val2) return 1;
            else if(val1 < val2) return -1;
        }
        return 0;
    }
};
