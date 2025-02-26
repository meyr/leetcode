
/* 最簡單是使用vector來實現 但是必須注意到細節
 * 現實生活不可能這樣解 因為memory會很大
 *
 */
class Allocator {
    vector<int> memory; // 0 : not used, > 0 : mID
public:
    Allocator(int n) {
        memory.resize(n);
    }
    
    // O(N)
    int allocate(int size, int mID) {
        int rtn{-1}, cnt{};
        for(int i = 0; i < memory.size(); ++i) {
            cnt = memory[i] > 0 ? 0 : cnt + 1;
            if(cnt == size) {
                for(int j = i - cnt + 1; j <= i; ++j)
                    memory[j] = mID;
                rtn = i - cnt + 1;
                break;
            }
        }
        return rtn;
    }
    
    //O(N)
    int freeMemory(int mID) {
        int rtn{};
        for(int i = 0; i < memory.size(); ++i) {
            if(memory[i] == mID) {
                rtn++;
                memory[i] = 0;
            }
        }
        return rtn;
    }
};
/*  參考 : https://leetcode.com/problems/design-memory-allocator/solutions/2899668/two-maps-by-votrubac-mw6q/
 *  自己寫出來的類似想法 無法AC
 *
 */
class Allocator {
    unordered_map<int, vector<pair<int, int>>> alloc;
    map<int, int> avail;
public:
    Allocator(int n) {
        avail.insert({0, n});
    }

    // O(N)
    int allocate(int size, int mID) {
        int rtn{-1};
        for(auto [idx, total] : avail) {
            if (total >= size) {
                alloc[mID].push_back({idx, size});
                avail.erase(idx);
                if (total > size)
                    avail.insert({idx + size, total - size});
                rtn = idx;
                break;
            }
        }
        return rtn;
    }

    // O(logN)
    int freeMemory(int mID) {
        int res = 0;
        if (auto it = alloc.find(mID); it != end(alloc)) { // 找不到表示沒有allocate過 直接返回
            for (auto [i, sz] : it->second) {
                auto ita = avail.insert({i, sz}).first; // 插入後順便取出iterator
                if (ita != begin(avail)) {
                    if (auto p = prev(ita); p->first + p->second == i) {
                        p->second += sz;
                        avail.erase(ita);
                        ita = p;
                    }
                }
                if (next(ita) != end(avail)) {
                    if (auto n = next(ita); i + sz == n->first) {
                        ita->second += n->second;
                        avail.erase(n);
                    }
                }
                res += sz;
            }
            alloc.erase(it);
        }
        return res;
    }
};
