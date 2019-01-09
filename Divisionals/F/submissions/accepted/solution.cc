#include <cstdio>

int main() {
	int m, n;
  scanf("%d %d", &m, &n);
  int total_length = 0;
  while (m--) {
    int l;
    scanf("%d", &l);
    total_length += l;
  }
  printf("%d\n", total_length / n + ((total_length % n) > 0));
}
