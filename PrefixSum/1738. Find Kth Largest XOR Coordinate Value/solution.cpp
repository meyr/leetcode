/*
    5, 2        5,   5^2
    1, 6        5^1, 5^2^1^6


    1, 2, 3     1,   1^2,           1^2^3
    4, 5, 6     1^4, 1^2^4^5,
    7, 8, 9     1^4^7, 1^2^4^5^7^8,


    和計算矩陣2D和類似
    並且使用minheap來得到第k個大的數值

    time  : O(MNlogK)
    space : O(K)
*/

class Solution {
public:
    int kthLargestValue(vector<vector<int>>& matrix, int k) {
        priority_queue<int, vector<int>, greater<int>> pq; //minheap
        auto push = [&](int v) {
            pq.push(v);
            if(pq.size() > k) pq.pop();
        };
        push(matrix[0][0]);
        for(int y = 1; y < matrix.size(); ++y) {
            matrix[y][0] ^= matrix[y - 1][0];
            push(matrix[y][0]);
        }
        for(int x = 1; x < matrix[0].size(); ++x) {
            matrix[0][x] ^= matrix[0][x - 1];
            push(matrix[0][x]);
        }
        for(int y = 1; y < matrix.size(); ++y) {
            for(int x = 1; x < matrix[0].size(); ++x) {
                matrix[y][x] ^= matrix[y - 1][x] ^ matrix[y][x - 1] ^
                                matrix[y - 1][x - 1];
                push(matrix[y][x]);
            }
        }
        return pq.top();
    }
};
