from heapq import *

[n, k] = [int(x) for x in input().split()]

stars = [ tuple(reversed([int(x) for x in input().split()])) for _ in range(n) ]
stars.sort()

pq = []

IMP, idx, ans = False, 0, 0
for i in range(k):
	while idx < n and stars[idx][0] <= i:
		heappush(pq, stars[idx][1])
		idx += 1
	if len(pq) == 0:
		IMP = True
		break
	ans += heappop(pq)

print("IMPOSSIBLE" if IMP else ans)
