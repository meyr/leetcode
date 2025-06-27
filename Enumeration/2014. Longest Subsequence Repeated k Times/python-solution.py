# 概念和cpp解法一樣 但是python寫起來比較簡潔
# 可以使用permutations()來產生所有的排列

class Solution:
    def longestSubsequenceRepeatedK(self, s: str, k: int) -> str:
        def check(s: str, p: str) -> bool:
            it = iter(s)
            return all(c in it for c in p)

        cnt = Counter(s)
        charset = [c for c,f in cnt.items() for _ in range(f // k)]
        charset.sort(reverse=True)

        for length in range(len(charset), 0, -1):
            for perm in permutations(charset, length):
                seq = ''.join(perm)
                if(check(s, seq * k)):
                    return seq
        return ''
