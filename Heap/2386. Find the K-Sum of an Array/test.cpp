#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
template<typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;
int main()
{
	vector<int> nums{1, 2, 3, 4};

	sort(begin(nums), end(nums));
	MinHeap<pair<int, int>> pq; //minheap
	pq.push(make_pair(nums[0], 0)); // minimal subsequence , not take any element
	cout << 0 << ","; // 1st minimal subsequence sum
	while(!pq.empty()) {
		auto [s, i] = pq.top(); pq.pop();
		cout << s << ",";
		if(i + 1 < nums.size()) {
			pq.push(make_pair(s + nums[i + 1], i + 1));
			pq.push(make_pair(s + nums[i + 1] - nums[i], i + 1));
		}
	}
	return 1;
}
