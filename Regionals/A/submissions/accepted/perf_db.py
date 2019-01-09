def doit():
    [n,L] = [int(x) for x in input().split()]
    length = sum([len(input()) for _ in range(n)])
    blanks = L - length
    if blanks < n-1:
        return False
    if n == 1:
        return blanks == 0
    return blanks % (n-1) == 0

print("Yes" if doit() else "No")
