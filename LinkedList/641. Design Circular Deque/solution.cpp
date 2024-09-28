/*  這題可以使用cpp內建的container(deque, list, vector等等)來建立
 *  這邊自己使用linked-list來實作
 *  另外使用shared_ptr來自動釋放資源
 *
 *  所有操作都是O(1) 
 */
class MyCircularDeque {
    struct node{
        int val;
        using spn = shared_ptr<node>;
        spn next, prev;
        node(int v) : val(v), next(nullptr), prev(nullptr){}
        node(int v, spn p, spn n) : val(v), prev(p), next(n){}
    };
    shared_ptr<node> root, front, rear;
    int maxsz, sz;
public:
    MyCircularDeque(int k) : maxsz(k), sz(0) {
        root = front = rear = make_shared<node>(-1);
    }
    
    bool insertFront(int value) {
        if(isFull()) return false;
        auto newnode = make_shared<node>(value, root, front);
        if(!newnode) return false;
        front->prev = newnode;
        root->next = newnode;
        front = newnode;
        if(rear == root) rear = newnode;
        sz++;
        return true;
    }
    
    bool insertLast(int value) {
        if(isFull()) return false;
        auto newnode = make_shared<node>(value, rear, nullptr);
        rear->next = newnode;
        rear = newnode;
        if(front == root) front = newnode;
        sz++;
        return true;
    }
    
    bool deleteFront() {
        if(isEmpty()) return false;
        if(front == rear) { // last node
            front = rear = root;
            root->next = nullptr;
        }else {
            front = front->next;
            front->prev = root;
            root->next = front;
        }
        --sz;
        return true;
    }
    
    bool deleteLast() {
        if(isEmpty()) return false;
        if(front == rear) { // last node
            front = rear = root;
            root->next = nullptr;
        } else {
            rear = rear->prev;
            rear->next = nullptr;
        }
        --sz;
        return true;
    }
    
    int getFront() {
        return front->val;
    }
    
    int getRear() {
        return rear->val;
    }
    
    bool isEmpty() {
        return sz == 0;
    }
    
    bool isFull() {
        return sz == maxsz;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
