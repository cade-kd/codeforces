#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int N = 200005;
int lastM[N], a[N];
void solve() {
  int n, q;
  int64_t sum = 0;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    sum += a[i];
  }
  int lastx = -1, lastT = 0;
  memset(lastM, 0, sizeof(lastM));
  for (int e = 1; e <= q; e++) {
    int t, i, x;
    cin >> t;
    if (t == 1) {
      cin >> i >> x;
      int y = a[i];
      if (lastM[i] < lastT) {
        y = lastx;
      }
      sum += x - y;
      lastM[i] = e;
      a[i] = x;
    }
    else {
      cin >> x;
      lastx = x;
      lastT = e;
      sum = 1LL * x * n;
    }
    cout << sum << endl;
  }


}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

}