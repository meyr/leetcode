/*
 *  右邊有比自己還大的val就必須刪除 --> 找出右邊比自己還大的 --> monotonic stack
 *
 *  time  : O(N)
 *  space : O(N)
 */

class Solution {
public:
    ListNode* removeNodes(ListNode* head) {
        vector<ListNode*> st;
        for(; head; head = head->next) {
            while(!st.empty() && head->val > st.back()->val)
                st.pop_back();
            if(!st.empty()) st.back()->next = head;
            st.push_back(head);
        }
        return st.front();
    }
};
