#include <iostream>

using namespace std;

void solve() {
  int64_t n, b;
  cin >> n;
  if ((n & 1) || n == 2) { cout << -1 << "\n"; }
  else if (n % 4) {
    cout << (n - 2) / 4 - (n - 6) / 12 << " " << n / 4 << endl;
  }
  else {
    cout << n / 4 - n / 12 << " " << n / 4 << endl;
  }


}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

}