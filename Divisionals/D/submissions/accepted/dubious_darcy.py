import fractions

n = int(input())
A = [int(x) for x in input().split()]

tot = 0
for i in range(n):
    tot += (i+1) * A[i] * (n-i)

ans = fractions.Fraction(tot, n * (n+1) // 2)
if ans.denominator == 1:
    print(ans,'/1',sep='')
else:
    print(ans)
