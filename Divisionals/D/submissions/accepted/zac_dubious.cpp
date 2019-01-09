#include <iostream>

long long cgcd(long long a, long long b) {
  while (b) {
    long long t = b;
    b = a % b;
    a = t;
  }
  return a;
}

int main()
{
  long long sum = 0;
  long long n;
  std::cin >> n;
  long long l = 1, r = n;
  long long count = (n * (n+1)) / 2;
  for  (long long i = 0; i < n; i++) {
    long long v;
    std::cin >> v;
    sum += (l * r) * v;
    l++;
    r--;
  }
  long long gcd;
  do {
    gcd = cgcd(sum, count);
    sum /= gcd;
    count /= gcd;
  } while (gcd > 1);

  std::cout << sum << "/" << count << std::endl;
}
