import sys

def mult(m1, m2):
  '''minimal-cost matrix product m1 * m2'''
  return [ [ min(m1[i][k] + m2[k][j] for k in range(n)) for j in range(n) ] for i in range(n) ]

n, m = map(int, sys.stdin.readline().split())
c = [ [ list(map(int, sys.stdin.readline().split())) for _ in range(n) ] ]

# matrix powers c[x] = c[0]^2^x, minimal costs for paths of length 2^x
k = 0
while min(c[k][0]) <= m:
  c.append(mult(c[k], c[k]))
  k += 1
# iteration stops if minimal cost from location 0 exceeds m
if k == 0:
  # get nowhere as every leg from location 0 exceeds m
  print(0)
  sys.exit(0)
# maximise l such that minimal cost from location 0 in c[0]^l is <= m
# binary search works as minimal cost increases with l
# construct l bit-by-bit, the k-th bit is 1
k -= 1
cc = c[k]
l = 2 ** k
k -= 1
while k >= 0:
  c1 = mult(cc, c[k]);
  # try 1 for the k-th bit of l
  if min(c1[0]) <= m:
    cc = c1
    l += 2 ** k
  k -= 1
print(l)

