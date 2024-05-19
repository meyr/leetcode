/*
 *  我的解法是真的去模擬game的走法 效率比較差因為資料還要push_back到後面
 *
 */ 
class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        if(k >= arr.size()) return *max_element(begin(arr), end(arr));
        unordered_map<int, int> m; //value, count
        unordered_set<int> pass;
        int i = 0, j = 1;
        while(1) {
            if(arr[i] > arr[j]) {
                if(++m[arr[i]] == k) return arr[i];
                arr.push_back(arr[j]);
                pass.insert(j++);
                while(j < arr.size() && (pass.count(j) || i == j)) ++j;
            } else {
                if(++m[arr[j]] == k) return arr[j];
                arr.push_back(arr[i]);
                pass.insert(i++);
                while(i < arr.size() && (pass.count(i) || i == j)) ++i;
            }
        }
        return -1;
    }
};
