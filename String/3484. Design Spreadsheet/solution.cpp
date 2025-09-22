/*  本題重點是如何使用 A11 這樣來存取spreadsheet 其中A代表column 11代表row
 *  使用string_view來觀察string比較有效率
 */

class Spreadsheet {
    /*      string_view轉int比較有效率的方法 使用from_chars
     *      舊的方法是先把string_view轉string再轉int  
     *                int rtn = stoi(string(sv));
     */
    static int sv2int(string_view sv) {
        int val;
        from_chars(sv.data(), sv.data() + sv.size(), val);
        return val;
    }
    class sheets{
        vector<vector<int>> vals;
        /*  拆解string成 <row, column>
         */
        pair<int, int> getRowColumn(string_view idx) const {
            pair<int, int> rtn;
            rtn.second = idx[0] - 'A';
            rtn.first = sv2int(idx.substr(1)) - 1;
            return rtn;
        }
    public:
        explicit sheets(int row) : vals(row, vector<int>(26)) {}
        int& operator[](const int& y, const int& x) {
            return vals[y][x];
        }
        const int& operator[](const int& y, const int& x) const{
            return const_cast<sheets*>(this)->operator[](y, x);
            //     ^^^^^^^^^^^^^^^^^^^^^^^^^   把 const sheet* 轉成 sheet* 這樣才可以呼叫non-const operator()[]
            //                         this->operator[](y, x)  呼叫non-const operator()[]
            //
            //     因為return type是const int&, non-const operator[]() 的回傳是int& 會轉成 const int& 再傳回去                    
        }
        int& operator[](string_view idx){
            auto [y, x] = getRowColumn(idx);
            return this->operator[](y, x);
        }
        const int& operator[](string_view idx) const {
            return const_cast<sheets*>(this)->operator[](idx);
        }
    };
    /*  判斷是欄位還是單純數字
     */
    bool isValid(string_view idx) {
        return idx.size() >= 2 and isalpha(idx[0]);
    }
    sheets st;
public:
    Spreadsheet(int rows) : st(rows) {
        
    }
    
    void setCell(string_view cell, int value) {
        st[cell] = value;
    }
    
    void resetCell(string_view cell) {
        st[cell] = 0;
    }
    /*  可能的輸入為 "=A12+B34"  兩個欄位相加
     *  另一種輸入為 "=123+234"  兩個數字相加
     *
     */
    int getValue(string_view formula) {
        int p = formula.find('+');                      // 先找出'+'的位置
        string_view cell1 = formula.substr(1, p - 1);
        string_view cell2 = formula.substr(p + 1);

        return (isValid(cell1) ? st[cell1] : sv2int(cell1)) + 
               (isValid(cell2) ? st[cell2] : sv2int(cell2));
    }
};
