/*  參考AI解答
 *
 */
class RangeModule {
private:
    map<int, int> intervals; // left, right
public:
    RangeModule() {}

    void addRange(int left, int right) {
        auto it = intervals.upper_bound(left);              // 只需要往前檢查一個
        if (it != intervals.begin()) {
            auto prev = std::prev(it);

            if (prev->second >= left) {                     // 如果前一個區間跟目前的 [left, right) 有重疊或相連，合併之
                left = prev->first;
                right = max(right, prev->second);           // __important__ 也要考慮right
                intervals.erase(prev);
            }
        }

        for (auto it = intervals.lower_bound(left); it != intervals.end() && it->first <= right; ) {    // 和[left, right)有重疊或相連 合併
            right = max(right, it->second);
            it = intervals.erase(it);                                                                   // __important__ 回傳刪除的下一個iterator
        }

        intervals[left] = right;
    }

    bool queryRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it == intervals.begin()) return false;
        auto prev = std::prev(it);
        return prev->second >= right;
    }

    void removeRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it != intervals.begin()) {
            auto prev = std::prev(it);
            if (prev->second > left) {                          // 如果前一個區間的右端點超過了 left，表示需要切割
                int old_right = prev->second;                   //                                                 old_right/prev->second
                prev->second = left;                            // 縮短前一個區間                         |--------------|                      prev->second = left
                if (old_right > right)                          // 如果原區間太長，切開後右邊還剩一段             |----------------|
                    intervals[right] = old_right;               //                                               left             right
            }                                                   //                                        |----------------------------------|
        }                                                       //                                                                 |---------| old_right

        for (auto it = intervals.lower_bound(left); it != intervals.end() && it->first < right; ) {
            if (it->second > right)                             // 區間右端點超出範圍，保留右邊剩餘部分
                intervals[right] = it->second;
            it = intervals.erase(it);                           // __important__ 回傳刪除的下一個iterator
        }
    }
};
/*  參考AI 使用dynamic segment tree 解法
 *
 */
struct Node {
    int lazy = -1; // -1: 無標記, 0: 移除, 1: 覆蓋
    bool val = false; // 目前區間是否完全被覆蓋
    Node *left = nullptr, *right = nullptr;
};

class RangeModule {
private:
    Node* root;
    const int MAX_RANGE = 1e9;

    void update(Node* &node, int L, int R, int qL, int qR, int val) {
        if (!node) node = new Node();

        // 區間完全包含
        if (qL <= L && R <= qR) {
            node->lazy = val;
            node->val = (val == 1);
            return;
        }

        pushDown(node);
        int mid = L + (R - L) / 2;
        if (qL <= mid) update(node->left, L, mid, qL, qR, val);
        if (qR > mid) update(node->right, mid + 1, R, qL, qR, val);

        // Push Up: 只有左右子節點都為真，父節點才為真
        node->val = (node->left && node->left->val) && (node->right && node->right->val);
    }

    bool query(Node* node, int L, int R, int qL, int qR) {
        if (!node) return false;
        if (node->lazy != -1) return node->lazy == 1;
        if (qL <= L && R <= qR) return node->val;

        int mid = L + (R - L) / 2;
        bool res = true;
        if (qL <= mid) res = res && query(node->left, L, mid, qL, qR);
        if (qR > mid) res = res && query(node->right, mid + 1, R, qL, qR);
        return res;
    }

    void pushDown(Node* node) {
        if (node->lazy == -1) return;
        if (!node->left) node->left = new Node();
        if (!node->right) node->right = new Node();

        node->left->lazy = node->right->lazy = node->lazy;
        node->left->val = node->right->val = (node->lazy == 1);
        node->lazy = -1;
    }

public:
    RangeModule() {
        root = new Node();
    }

    void addRange(int left, int right) {
        // 注意：題目是左閉右開 [left, right)，轉成線段樹常用的全閉區間 [left, right-1]
        update(root, 0, MAX_RANGE, left, right - 1, 1);
    }

    bool queryRange(int left, int right) {
        return query(root, 0, MAX_RANGE, left, right - 1);
    }

    void removeRange(int left, int right) {
        update(root, 0, MAX_RANGE, left, right - 1, 0);
    }
};
