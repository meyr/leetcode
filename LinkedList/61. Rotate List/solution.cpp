/*  照題意先找出全部長度 再找出切割點
 *  雖然也是可以AC但是感覺一不小心會有bug
 *
 * time  : O(N + N) = O(N)
 * space : O(1)
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next || k == 0) return head;
        int sz{1};
        ListNode* p = head;
        while(p->next) {
            p = p->next;
            sz++;
        }
        ListNode* last = p;
        k %= sz;
        if(k == 0) return head;
        int count = sz - k;
        p = head;
        while(count) {
            auto nxt = p->next;
            if(count == 1) p->next = nullptr;
            p = nxt;
            count--;
        }
        last->next = head;
        return p;
    }
};
/* 一樣想法改把node存在vector內方便操作
 *
 * time  : O(N)
 * space : O(N)
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head || !head->next || k == 0) return head;
        vector<ListNode*> nodes;
        while(head) {
            nodes.push_back(head);
            head = head->next;
        }
        k %= nodes.size();
        if(k == 0) return nodes[0];
        int count = nodes.size() - k;
        nodes[count - 1]->next = nullptr;
        nodes.back()->next = nodes.front();
        return nodes[count];
    }
};
