[n, budget] = [int(x) for x in input().split()]

pow2 = [ [ [int(x) for x in input().split() ] for _ in range(n) ] ]

power = 0
while True:
	power += 1
	pow2.append( [ [ min(budget+1, min(pow2[power-1][i][k] + pow2[power-1][k][j] for k in range(n))) for j in range(n)] for i in range(n)] )
	if min(pow2[power][0]) > budget:
		break

ans = [ [ budget+1 for x in range(n) ] for y in range(n) ]
ans[0][0] = 0

the_answer = 0
for p in range(power, -1, -1):
	tmp = [ [ min(budget+1, min(ans[i][k] + pow2[p][k][j] for k in range(n))) for j in range(n)] for i in range(n)]
	if min(tmp[0]) <= budget:
		ans = tmp
		the_answer += pow(2, p)

print(the_answer)
