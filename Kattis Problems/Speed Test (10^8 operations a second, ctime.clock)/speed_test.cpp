#include <bits/stdc++.h>
using namespace std;

int main() {
  clock_t begin = clock();
  long long counter = 0;
  int N = 1e5; //1e5 = 100000 // try adding a few more zero digitS at the back of this variable to make your computer hangs...
  for (int i = 0; i < N; i++) { // O(c * N^2), c is 'small' if you leave line 12 commented, but c is BIG if you uncomment it
    // printf("i = %d\n", i);
    for (int j = 1; j < N; j*=2) { // O(log N)
    // for (int j = 0; j < N; j++) { // O(N)
      counter++; // this operation is O(1), and fast, let's say 0.0000000001 s
      // but if you uncomment the next line, the same O(N^2) algorithm will be noticeably much slower
      // printf(" counter = %d\n", counter); // this operation is 'heavy', let's say 0.01s per printf statement...
    }
  }
  printf("counter = %lld, computed in = %fs\n", counter, (double)(clock()-begin)/CLOCKS_PER_SEC);
  return 0;
}