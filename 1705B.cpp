#include<bits/stdc++.h>
using namespace std;
template<typename T1, typename T2>
istream& operator>>(istream& ins,
  pair<T1, T2>& v) {
  ins >> v.first >> v.second;
  return ins;
}

template<typename T, size_t N>
istream& operator>>(istream& ins,
  array<T, N>& v) {
  for (int i = 0; i < int(N); i++) cin >> v[i];
  return ins;
}

template<typename T>
istream& operator>>(istream& ins,
  vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) ins >> v[i];
  return ins;
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  cin >> a;
  int b = 0;
  int64_t ans = 0;
  for (int i = 1; i < n; i++) {
    while (b < n && a[b] == 0) b++;
    if (i <= b || a[i] != 0) continue;
    a[i] = 1;
    a[b]--;
    ans++;
  }

  for (int i = 0; i < n - 1;i++) {
    ans += a[i];
  }
  cout << ans << "\n";

}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}