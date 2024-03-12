/**
 *    上一個solution因為是往後看pfs 所以如果連接起來 必須修正pfs和hash table
 *    如果是往前看 就不用修正pfs和hash table
 *   
 *    [1, 2, 3, -3, -2]
 *     1, 3, 6,  3,  1    prefix sum, first loop
 *     1,            1    看到有相同的pfs 連接 second loop
 *
 */
class Solution {
public:
    ListNode* removeZeroSumSublists(ListNode* head) {
        ListNode* dummy = new ListNode(0);
        dummy->next = head;
        int prefix = 0;
        unordered_map<int, ListNode*> seen;
        for (ListNode* i = dummy; i; i = i->next) {
            seen[prefix += i->val] = i;
        }
        prefix = 0;
        for (ListNode* i = dummy; i; i = i->next) {
            i->next = seen[prefix += i->val]->next;
        }
        return dummy->next;
    }
};
