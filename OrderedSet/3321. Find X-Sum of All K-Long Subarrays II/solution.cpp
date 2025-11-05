/*  試了很多版本最後決定使用兩個priority_queue來寫 因為我們要記錄前x個最大的element
 *  因為要維護前x個最大element
 *
 *  所以要加入element都要先推入bottom, 然後再推到top, 如果top太多了再推回bottom
 *  這樣才可以保證最大值都在top --> 詳見OrderSum實作
 *
 *  每個priority_queue使用set來實作 因為我要可以前後都可以取出 和可以移除任意element
 *  SumSet除了使用set還會紀錄份入element的總和 這樣不用重新計算 --> 詳見SumSet實作
 *  
 *  只要是排序的題目 都可以使用兩個priority_queue來實作
 *
 */
using pii = pair<int,int>;
class SumSet {
    long long sum{};
    int sz{};
    std::set<pii> st;

    pii pop(std::set<pii>::iterator it) {
        auto p = *it;
        sum -= 1LL * p.first * p.second;
        st.erase(it);
        return p;
    }

public:
    SumSet(int _sz) : sz(_sz) {}
    int size() const { return st.size(); }
    bool empty() const { return st.empty(); }
    bool full() const { return (int)st.size() == sz; }
    long long getSum() const { return sum; }

    void erase(const pii &p) {
        auto it = st.find(p);
        if (it == st.end()) return;
        pop(it);
    }

    void push(const pii &p) {
        if (p.first == 0) return;
        sum += 1LL * p.first * p.second;
        st.insert(p);
    }

    pii pop_top() {
        if (empty()) return {};
        auto it = prev(st.end());
        return pop(it);
    }

    pii pop_back() {
        if (empty()) return {};
        auto it = st.begin();
        return pop(it);
    }
};

class OrderSum {
    int sz;
    SumSet top, bottom;

public:
    OrderSum(int _sz) : sz(_sz), top(_sz), bottom(100000) {}

    void push(const pii &p) {
        if (p.first == 0) return;
        bottom.push(p);
        top.push(bottom.pop_top());
        if (top.size() > sz)
            bottom.push(top.pop_back());
    }

    void erase(const pii &p) {
        top.erase(p);
        bottom.erase(p);
        if (top.size() < sz && !bottom.empty()) {   //__important__ 如果移除後top數量少於x 必須從bottom補一個上來
            top.push(bottom.pop_top());
        }
    }

    long long getSum() const { return top.getSum(); }
};

class Solution {
public:
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        OrderSum os(x);
        unordered_map<int,int> count;
        vector<long long> ans;
        int n = nums.size();

        for (int i = 0; i < n; ++i) {
            int val = nums[i];

            os.erase({count[val], val});
            count[val]++;
            os.push({count[val], val});

            if (i >= k - 1) {
                ans.push_back(os.getSum());

                int leftVal = nums[i - k + 1];
                os.erase({count[leftVal], leftVal});
                count[leftVal]--;
                if (count[leftVal] > 0)
                    os.push({count[leftVal], leftVal});
            }
        }
        return ans;
    }
};

