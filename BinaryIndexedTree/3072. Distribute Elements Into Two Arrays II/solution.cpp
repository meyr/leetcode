/*
 *  因為要數大於某個數值的個數 很適合使用BIT --> getRangeSum(n + 1, mx)
 *  但是input number range 為 1 <= nums[i] <= 1e9 不可能在class BIT中使用vector<int> v; 因為太大了
 *  所以使用unordered_map
 *
 *  但是這樣的解法在最後的testcase會TLE
 *
 */
class FenwickTree{
    int sz;
    unordered_map<int,int> tree;
public:
    FenwickTree(int n) : sz(n + 1) {}
    int prefixSum(int pos){
        int sum = 0;
        while(pos > 0){
            sum += tree[pos];
            pos -= pos & -pos;
        }
        return sum;
    }
    int sumRange(int start, int end){
        return prefixSum(end)-prefixSum(start-1);
    }
    void update(int pos, int val){
        while(pos <= sz){
            tree[pos] += val;
            pos += pos & -pos;
        }
    }
};

class Solution {
    void append(vector<int>& arr, FenwickTree& f, int val) {
        arr.push_back(val);
        f.update(val, 1);
    }
public:
    vector<int> resultArray(vector<int>& nums) {
        vector<int> arr1, arr2;
        int mx = *max_element(begin(nums), end(nums));
        FenwickTree f1(mx), f2(mx);
        append(arr1, f1, nums[0]);
        append(arr2, f2, nums[1]);

        for(int j = 2; j < nums.size(); j++){
            int n = nums[j];
         
            int ctr1 = f1.sumRange(n+1, mx);
            int ctr2 = f2.sumRange(n+1, mx);
            
            if(ctr1 > ctr2)
                append(arr1, f1, n);
            else if(ctr2 > ctr1)
                append(arr2, f2, n);
            else if(arr1.size() > arr2.size())
                append(arr2, f2, n);
            else
                append(arr1, f1, n);
            
        }
        
        for(int n :arr2) arr1.push_back(n);
        return arr1;
    }
};
