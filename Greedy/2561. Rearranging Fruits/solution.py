class Solution:
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:
        count = Counter()
        small = float('inf')        # python無法像cpp一樣使用iterator取得最小值
        for f in basket1:
            count[f] += 1
            small = min(small, f)
        for f in basket2:
            count[f] -= 1
            small = min(small, f)
        swaps = []
        res = 0
        for f, c in count.items():
            if c % 2:
                return -1
            swaps.extend([f] * (abs(c) // 2))   # python可以直接延伸list
        swaps.sort()
        return sum(min(small * 2, x) for x in swaps[:len(swaps) // 2])  # 使用list slicing取得前半資料
