/*
 *      參考leetcode官方解答
 *
 */
class Solution {
    struct seg{
        int left{INT_MAX}, right;
        bool operator<(const seg& rhs) const {
            if(right == rhs.right)          // right 一樣就比較短的往前排
                return left > rhs.left;
            return right < rhs.right;       // 先結束的排前面
        }
    };
public:
    vector<string> maxNumOfSubstrings(string s) {
        // 1. 統計每個char的left和right
        vector<seg> segs(26);
        for(int i = 0; i < s.size(); ++i) {
            int charidx = s[i] - 'a';
            segs[charidx].left = min(segs[charidx].left, i);
            segs[charidx].right = i;
        }

        // 2. 擴張每個seg, 因為一個substring [left, right] 中間可能會包含其他char, 這些char也會有範圍
        //
        //  case 1: 出現的substring在原本的[left, right]中間 則可以忽略
        //
        //    |-------|
        //      *---*
        //
        //  other case:     都會造成[left, right]變大 因為妳為了包含原本的char, 但是其他char會造成[left, right]變大
        //                  所以 left  = min(left, rhs.left)
        //                       right = max(right, rhs.right)
        //
        //    |-------|            |------|     |-------|
        //       *---------*   *-------*      *-------------*
        //
        for (int i = 0; i < 26; ++i) {
            if (segs[i].left != -1) {
                for (int j = segs[i].left; j <= segs[i].right; ++j) {
                    int charIdx = s[j] - 'a';
                    if (segs[i].left <= segs[charIdx].left &&
                        segs[charIdx].right <= segs[i].right) {
                        continue;
                    }
                    segs[i].left = min(segs[i].left, segs[charIdx].left);
                    segs[i].right = max(segs[i].right, segs[charIdx].right);
                    j = segs[i].left;   // __important__ 更新完 [left, right]之後 left需要從新的left開始
                }
            }
        }

        // 3. 排序segs
        //    + 越早結束的排越前面
        //    + 結束時間一樣的短的排在前面
        //
        //    Greedy poing: 取越短越早結束的 可以得到越多substring
        sort(begin(segs), end(segs));
        int right{-1};
        vector<string> ans;
        for(auto& seg : segs) {
            if(seg.left == INT_MAX) continue;
            if(right < seg.left) {  // 沒有重疊
                right = seg.right;
                ans.push_back(s.substr(seg.left, seg.right - seg.left + 1));
            }
        }

        return ans;
    }
};

