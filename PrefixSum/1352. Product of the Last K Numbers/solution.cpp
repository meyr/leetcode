/*  一開始就考慮類似prefix sum的作法 但是必須避開有0的情況
 *  所以使用vector<int> 來記錄products 如果遇到0就清光products 因為取超過0都會等於0
 *  vector<int> products{1} 必須有個預設element 1 才有辦法計算全部都取的情況
 *
 */
class ProductOfNumbers {
    int zeroidx{-1};            // 紀錄zero index的位置
    vector<int> products{1};    // __important__ 預設情況, 才可以計算全部都取的情況
public:
    ProductOfNumbers() {

    }

    // time  : O(1)
    void add(int num) {
        if(num == 0) {                          // 遇到0 回到預設狀態
            zeroidx = 1;
            products = move(vector<int>{1});
        } else {
            zeroidx += zeroidx > 0;
            products.push_back(products.back() * num);  // 計算prefix product
        }
    }

    // time  : O(1)
    int getProduct(int k) {
        int rtn;
        if(zeroidx > 0 && k >= zeroidx) rtn = 0;    // 當取的k超過0 直接返回0
        else {
            int sz = products.size();
            rtn = products.back() / products[sz - k - 1];
        }
        return rtn;
    }
};
/* 參考解答 想法一樣 其實zeroidx就是products的大小 所以不用紀錄 
 *
 */
class ProductOfNumbers {
public:
    vector<int> pre{1};
    ProductOfNumbers() {}

    void add(int num) {
        if (num != 0) {
            pre.push_back(num * pre.back());
        } else {
            pre.clear();
            pre.push_back(1);
        }
    }

    int getProduct(int k) {
        return k < pre.size() ? pre.back() / pre[pre.size() - k - 1] : 0;
    }
};
