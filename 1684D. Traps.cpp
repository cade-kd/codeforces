#include<bits/stdc++.h>
using namespace std;


void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] += i;
  }
  n -= k + 1;
  sort(a.begin(), a.end());
  int64_t cost = accumulate(a.begin(), a.begin() + n + 1, 0LL) - (1LL + n) * n / 2;

  cout << cost << "\n";

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