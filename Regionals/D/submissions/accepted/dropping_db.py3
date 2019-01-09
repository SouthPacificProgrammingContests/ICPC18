
n = int(input())
A = [int(x) for x in input().split()]
A.append(0)

forced_right = 0
ans = "YES"
for i in range(n):
    if A[i] < forced_right:
        ans = "NO"
    forced_right += max(0, A[i+1] - A[i])

print(ans)
