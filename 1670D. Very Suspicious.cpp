#include<bits/stdc++.h>
using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t, n;
  cin >> t;
  while (t--) {
    cin >> n;
    int res = 100000000;
    for (int y = 0; y < 3; y++) {
      int a = 6, b = 4 * y, c = 2 * (y == 2) - n;
      int x = 0;
      if (n > 10 || b * b - 4 * a * c > 0) {
        x = ceil((-b + sqrt(b * b - 4LL * a * c)) / (2 * a));
      }
      res = min(res, 3 * x + y);
    }
    cout << res << endl;
  }

}