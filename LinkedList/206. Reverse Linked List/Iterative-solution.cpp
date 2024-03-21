class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode* next = head->next;
        head->next = nullptr; // head為最後一個node
        while(next) {
            ListNode* nnext = next->next;
            next->next = head;
            head = next;
            next = nnext;
        }
        return head;
    }
};
