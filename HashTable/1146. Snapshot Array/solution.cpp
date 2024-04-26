class SnapshotArray {
    vector<vector<pair<int, int>>> hist; // index, <snap_id, val>
    int snap_id{};
public:
    SnapshotArray(int length) {
        hist.resize(length, vector<pair<int, int>>(1, {0, 0}));
    }
    
    void set(int index, int val) {
        if(hist[index].back().first != snap_id) hist[index].push_back({snap_id, 0});
        hist[index].back().second = val;
    }
    
    int snap() {
        return snap_id++;
    }
    
    int get(int index, int snap_id) {
        vector<pair<int, int>>& vp = hist[index];
        pair<int, int> target = {snap_id, INT_MAX};
        auto it = upper_bound(begin(vp), end(vp), target);
        return prev(it)->second;
    }
};
