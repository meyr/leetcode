class Solution:
    def minCost(self, colors: str, neededTime: List[int]) -> int:
        total = sum(neededTime)
        remain, prev, maxv = 0, 'A', 0
        colors += 'A'
        neededTime += [0]
        for cur, time in zip(colors, neededTime):
            if prev != cur:
                remain += maxv
                maxv = time
            else:
                maxv = max(maxv, time)
            prev = cur
        return total - remain
