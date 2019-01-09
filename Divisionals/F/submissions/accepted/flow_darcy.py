[m,n] = [int(x) for x in input().split()]
tot = sum([int(input()) for _ in range(m)])
print( (tot + n - 1) // n )
