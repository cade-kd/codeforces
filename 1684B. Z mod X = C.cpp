#include<bits/stdc++.h>
using namespace std;

void solve() {
  int a, b, c;
  cin >> a >> b >> c;

  cout << int64_t(c) * b + a << " " << b << " " << c << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}