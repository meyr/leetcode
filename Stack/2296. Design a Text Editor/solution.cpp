/* 最直覺的方法是使用一個string然後加加減減
 * 但是這個方法MLE 應該是addText那邊用太多記憶體了
 *
 */
class TextEditor {
    string str;
    int idx{};
public:
    TextEditor() {

    }

    void addText(string text) {
        string prev = str.substr(0, idx);
        string next = str.substr(idx);
        string newstr = prev + text + next;
        str = move(newstr);
        idx += text.size();
        //cout << "addText : " << str << "," << idx << endl;
    }

    int deleteText(int k) {
        int si = max(0, idx - k);
        int len = si;
        string prev = str.substr(0, len);
        string next = str.substr(idx);
        string newstr = prev + next;
        str = move(newstr);
        int rtn = min(idx, k);
        idx = si;
        //cout << "deleteText : " << str << "," << idx << endl;
        return rtn;
    }

    string cursorLeft(int k) {
        idx = max(0, idx - k);
        int si = max(0, idx - 10);
        int len = idx - si;
        //cout << "cursorLeft : " << str << "," << idx << "," << str.substr(si, len) << endl;
        return str.substr(si, len);
    }

    string cursorRight(int k) {
        idx = min((int)str.size(), idx + k);
        int si = max(0, idx - 10);
        int len = idx - si;
        //cout << "cursorRight : " << str << "," << idx << "," << str.substr(si, len) << endl;
        return str.substr(si, len);
    }
};
/*
 * 後來意識到這可已用deque代表前面的stirng, stack代表後面的string
 * 其實deque也只操作back, 所以可以用兩個stack來表示 cursor之前的string和之後的string
 *
 * time  : O(K) 所有的API都是O(K) K : text.size() 或是 input argument k
 *
 */
class TextEditor {
    stack<char> prev, next;
    string getReturn(stack<char>& st) {
        string rtn{};
        for(int i = 0; i < 10 && !st.empty(); ++i) {
            rtn.push_back(st.top());
            st.pop();
        }
        reverse(begin(rtn), end(rtn));
        for(int i = 0; i < rtn.size(); ++i) st.push(rtn[i]);
        return move(rtn);
    }
public:
    TextEditor() {

    }

    void addText(string text) {
        for(auto& c : text)
            prev.push(c);
    }

    int deleteText(int k) {
        int rtn{};
        while(k-- && !prev.empty()) {
            prev.pop();
            rtn++;
        }
        return rtn;
    }

    string cursorLeft(int k) {
        while(k-- && !prev.empty()) {
            next.push(prev.top());
            prev.pop();
        }
        return getReturn(prev);
    }

    string cursorRight(int k) {
        while(k-- && !next.empty()) {
            prev.push(next.top());
            next.pop();
        }
        return getReturn(prev);
    }
};
