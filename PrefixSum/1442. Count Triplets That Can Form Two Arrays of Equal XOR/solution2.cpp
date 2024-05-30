/*
 *  參考 : https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/solutions/623747/java-c-python-one-pass-o-n-4-to-o-n/ 
 *
    a == b
    a ^ a == b ^ a
    0 == a ^ b
    0 == arr[i]^ arr[i + 1] ^ ... ^ arr[j - 1] ^ arr[j] ^ ... ^ arr[k]
    0 == prefix[k] ^ prefix[i - 1]
    prefix[i - 1] == prefix[k]
    prefix[i] == prefix[k + 1]
    決定了i, k剩下就是決定j
    j can be any number that i < j <= k,

    time  : O(N + N + N^2) = O(N^2)
    space : O(1) 
*/

class Solution {
public:
    int countTriplets(vector<int>& A) {
        A.insert(A.begin(), 0); //O(N)
        int n = A.size(), res = 0;
        for (int i = 1; i < n; ++i) // O(N)
            A[i] ^= A[i - 1];
        for (int i = 0; i < n; ++i) // O(N^2)
            for (int j = i + 1; j < n; ++j)
                if (A[i] == A[j])
                    res += j - i - 1;
        return res;
    }
};
