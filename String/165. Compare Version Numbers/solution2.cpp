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
