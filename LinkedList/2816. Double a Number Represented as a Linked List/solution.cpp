/*
 *  很直覺從最後一個node回推回來 -> preorder
 *
 *  time  : O(N) , 每個node都會走訪兩次
 *  space : O(N) , recursive使用的stack
 */
class Solution {
    int helper(ListNode* head) {
        int c{};
        if(head->next) c = helper(head->next);
        int s = head->val * 2 + c;
        head->val = s % 10;
        return s / 10;
    }
public:
    ListNode* doubleIt(ListNode* head) {
        int c = helper(head);
        if(c) return new ListNode(c, head);
        else return head;
    }
};
