"""
    根據c++解答的想法
    去掉左邊所有連續的'L' directions.lstrip('L')
    再去掉右邊連續的'R'   directions.rstrip('R')
    計算長度減去出現的'S'數目就是解答
"""
class Solution:
    def countCollisions(self, directions: str) -> int:
        dirs = directions.lstrip('L').rstrip('R')
        return len(dirs) - dirs.count('S')

