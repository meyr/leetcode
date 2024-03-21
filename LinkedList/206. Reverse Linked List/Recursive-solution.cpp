class Solution {
    ListNode* helper(ListNode *head) {
        ListNode* next = head->next;
        if(!next) return head;
        head->next = nullptr;
        ListNode *newhead = helper(next);
        next->next = head;
        return newhead;
    }
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;
        return helper(head);
    }
};
