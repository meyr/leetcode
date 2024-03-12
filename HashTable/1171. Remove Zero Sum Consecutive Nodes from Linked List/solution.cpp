/**
 *   要找出sum為0 等於找出相同的prefix sum
 *   使用unordered_map來記錄找過的pfs
 *
 *   找到之後使用recursive來重頭開始找 因為必須重頭開始計算
 *   
 */
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* fakeroot = new ListNode(0, head);
        unordered_map<int, ListNode*> m;
        m[0] = fakeroot;
        int pfs{};
        while(head) {
            pfs += head->val;
            if(m.count(pfs)) {
                m[pfs]->next = head->next;
                return removeZeroSumSublists(fakeroot->next);
            }
            m[pfs] = head;
            head = head->next;
        }
        return fakeroot->next;
    }
};
