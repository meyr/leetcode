class MovieRentingSystem {
    // 根據題意 search的時候 會找出最小的price如果price一樣就根據 shop id排序 set剛好可以符合
    unordered_map<int, set<vector<int>>> movies; // id of movides, <price, shop id>
    // 根據shop, move來查詢價格
    unordered_map<long long, int> prices; // <shop, move>, price
    // 出借的movie中依據 price, shop和movie來排序
    set<vector<int>> rented; // <price, shop, movie> 
public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for(const auto& entry : entries) {
            int shop = entry[0];
            int movie = entry[1];
            int price = entry[2];
            movies[movie].insert({price, shop});
            prices[((long long)shop << 32) | movie] = price;
        }
    }
    
    vector<int> search(int movie) {
        vector<int> rtn;
        const auto& cur = movies[movie];
        auto it = cur.begin();
        for(int i = 0; i < 5 && it != cur.end(); ++i, ++it)
            rtn.push_back((*it)[1]);
        return rtn;
    }
    
    void rent(int shop, int movie) {
        int price = prices[((long long)shop << 32) | movie];
        movies[movie].erase({price, shop});
        rented.insert({price, shop, movie});
    }
    
    void drop(int shop, int movie) {
        int price = prices[((long long)shop << 32) | movie];
        movies[movie].insert({price, shop});
        rented.erase({price, shop, movie});
    }
    
    vector<vector<int>> report() {
        vector<vector<int>> rtn;
        auto it = rented.begin();
        for(int i = 0; i < 5 && it != rented.cend(); ++it, ++i)
            rtn.push_back({(*it)[1], (*it)[2]});
        return rtn;
    }
};
