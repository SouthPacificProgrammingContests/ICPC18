n = int(input())
A = [int(x) for x in input().split()]

M = dict()
ctr = 0
for i in range(n):
    if not A[i] in M:
        M[A[i]] = ctr
        ctr += 1
    A[i] = M[A[i]]

used = [0 for _ in range(ctr)]

num_used, r = 0, 0
while num_used < ctr:
    used[A[r]] += 1
    if used[A[r]] == 1:
        num_used += 1
    r += 1

ans = r
for l in range(n):
    if r == n: break
    used[A[l]] -= 1
    if used[A[l]] == 0:
        while r < n and used[A[l]] == 0:
            used[A[r]] += 1
            r += 1
        size = r-l-1
        if used[A[l]] == 0: size += 1
        ans = max(ans, size)

print(ans)
