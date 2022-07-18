#include<bits/stdc++.h>
using namespace std;
#define LOCAL

void solve() {
  int n;
  cin >> n;
  vector<int> v;
  int X = -1, p;
  for (int i = 0; i < n; i++) {
    cin >> p;
    if (p != i) X &= p;
  }
  cout << X << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}