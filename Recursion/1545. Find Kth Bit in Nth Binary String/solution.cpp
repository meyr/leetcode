/*  因為事先已經知道是recursive的題目 所以就是遞減n來推算k的位置所在char
 *
 *  time  : O(N)
 *  space : O(N)
 */
class Solution {
    int helper(int n, int k) {
        if(n == 1) return 0;
        else if(k > 1 && (k & (k - 1)) == 0) return 1;
        else if(k > pow(2, n - 1)) return !helper(n - 1, pow(2, n) - k);
        else return helper(n - 1, k);
    }
public:
    char findKthBit(int n, int k) {
        return helper(n, k) + '0';
    }
};
/*
    1 = 0                 1
    2 = 011               3
    3 = 0111001           7
    4 = 01110011 0110001  15

    1, 2, 3, 4, 5, 6, 7
    0, 1, 1, 1, 0, 0, 1

*/
/* 2026/03/03 daily challenge
 *
 *  因為 n <= 20 所以先計算每個n代表的長度 Nk = Nk-1 * 2 + 1 目前的n是前一個的兩倍+1 --> 其實每一層的長度是pow(2, n) - 1, 中間點就是剛好2的倍數
 *  找出中心點 並且比較中心點和k
 *
 */
class Solution {
    vector<int> length;
    int helper(int n, int k) {
        int mid = (length[n] + 1) / 2;
        if(n == 1) return 0;
        else if(k == mid) return 1;
        else if(k > mid) return !helper(n - 1, length[n] - k + 1);
        else return helper(n - 1, k);
    }
public:
    char findKthBit(int n, int k) {
        length.resize(21);
        length[1] = 1;
        for(int i = 2; i < length.size(); ++i) length[i] = length[i - 1] * 2 + 1;
        return helper(n, k) + '0';
    }
};
