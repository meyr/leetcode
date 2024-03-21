/*
 *  直接修改linked list value也不失為ㄧ個好方法
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        stack<int> st;
        ListNode *p = head;
        while(p) {
            st.push(p->val);
            p = p->next;
        }
        p = head;
        while(!st.empty()) {
            p->val = st.top();
            st.pop();
            p = p->next;
        }
        return head;
    }
};
