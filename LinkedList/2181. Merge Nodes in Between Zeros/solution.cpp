/**
 * [0, 3, 1, 0, 4, 5, 2, 0] 使用recursive來解決問題 先找出固定的pattern
 *     -------
 *              ----------
 *
 * 因為題目說一定會有0在前後 而且不會有連續兩個0
 * 所以helper的head都是從第一個非0開始 直到找到p->next->val == 0
 *
 * time  : O(N)
 * space : O(1)
 */
class Solution {
    ListNode* helper(ListNode* head) {
        if(!head) return head;
        while(head->next->val != 0) {
            head->next->val += head->val;
            head = head->next;
        }
        head->next = helper(head->next->next);
        return head;
    }
public:
    ListNode* mergeNodes(ListNode* head) {
        return helper(head->next);
    }
};
