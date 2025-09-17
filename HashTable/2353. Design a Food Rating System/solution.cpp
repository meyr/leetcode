/*  照題意設計相對應的data struct
 *
 *  space : O(N)
 */
class FoodRatings {
    using pis = pair<int, string>;
    // 使用PariCompare來對set中的pair進行排序
    // rating高的在前面 rating一樣就用名字排序
    struct PairCompare {
        bool operator()(const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) const {
            if(a.first > b.first) return true;
            else if(a.first == b.first) return a.second < b.second;
            return false;
        }
    };
    unordered_map<string, pis> f2rc;
    unordered_map<string, set<pis,PairCompare>> db;
public:
    // time : O(NlogN)
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        int sz = foods.size();
        for(int i = 0; i < sz; ++i) {
            string f = foods[i];
            string c = cuisines[i];
            int r = ratings[i];
            f2rc[f] = make_pair(r, c);
            db[c].insert({r, f});
        }
    }

    // O(1)
    void changeRating(string food, int newRating) {
        auto& [r, c] = f2rc[food];
        db[c].erase({r, food});
        db[c].insert({newRating, food});
        r = newRating;                      // __important__ 記得要修改rating
    }

    // O(1)
    string highestRated(string cuisine) {
        return db[cuisine].begin()->second;
    }
};
