class RangeFreqQuery {
    unordered_map<int, vector<int>> m;
public:
    RangeFreqQuery(vector<int>& arr) {
        for(int i = 0; i < arr.size(); ++i)
            m[arr[i]].push_back(i);
    }
    
    int query(int left, int right, int value) {
        auto it1 = lower_bound(begin(m[value]), end(m[value]), left);
        auto it2 = upper_bound(begin(m[value]), end(m[value]), right);
        return it2 - it1; 
    }
};
