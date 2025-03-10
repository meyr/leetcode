/*  使用sliding window的解法 但是某些testcast會出錯
 *  
 *  sliding window不適合條件是 == k, 比較適合 >= k 或是 <= k
 *  因為會有一些情況沒計算到
 *
 *  參考 : 1248. Count Number of Nice Subarrays
 */
class Solution {
public:
    long long countOfSubstrings(string word, int k) {
        unordered_map<char, int> vowel{{'a', 0}, {'e', 1}, {'i', 2}, {'o', 3}, {'u', 4}};
        unordered_map<char, int> m;
        long long ans{};
        int total{}, list{};
        for(int right = 0, left = 0; right < word.size(); ++right) {
            char c = word[right];
            if(vowel.count(c)) {
                m[c]++;
                total++;
                list |= 1 << vowel[c];
            }
            while(left < right && right - left + 1 - total > k) {
                char& c = word[left++];
                if(vowel.count(c)) {
                    m[c]--;
                    total--;
                    if(m[c] == 0)
                        list &= ~(1 << vowel[c]);
                }
            }
            while((list == 0b11111) && (right - left + 1 - total == k)) {
                cout << left << "," << right << endl;
                ans++;
                char c = word[left++];
                if(vowel.count(c)) {
                    m[c]--;
                    total--;
                    if(m[c] == 0)
                        list ^= 1 << vowel[c];
                }
            }
        }
        return ans;
    }
};

/*  參考 :
 *  https://leetcode.com/problems/count-of-substrings-containing-every-vowel-and-k-consonants-ii/solutions/5846568/sliding-window-easy-c-code-on-time-o1-sp-76nt/
 *
 *  原本的條件是 vowel滿足at least 5個 且 consonants == k
 *  這邊的helper()是計算 vowel不滿足at least5個 或 consonants <= k
 *
 *  time  : O(N)
 *  sapce : O(1)
 */
class Solution {
    unordered_set<char> vowel = {'a', 'e', 'i', 'o', 'u'};
public:
    long long helper(string word, int k) {
        long long cnt = 0;
        unordered_map<char, int> m;
        for (int r = 0, l = 0, cons = 0; r < word.size(); r++) {
            char& c = word[r];
            if (vowel.count(c)) m[c]++;
            else cons++;
            while (m.size() == 5 && cons > k) {
                char& d = word[l++];
                if (vowel.count(d)) {
                    if (--m[d] == 0)
                        m.erase(d);
                } else
                    cons--;
            }
            cnt += (r - l + 1); // 因為經過上面的while 所以裡面的已right結尾的substring都滿足helper計算條件
        }
        return cnt;
    }
    long long countOfSubstrings(string word, int k) {
        return helper(word, k) - helper(word, k - 1);
    }
};
