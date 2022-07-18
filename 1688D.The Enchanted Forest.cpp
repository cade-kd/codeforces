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
  int64_t n, k;
  cin >> n >> k;
  vector<int64_t> pre(n + 1);
  for (int i = 1;i <= n;i++) {
    int a;
    cin >> a;
    pre[i] = a + pre[i - 1];
  }
  int64_t t = min(k, n);
  int64_t suma = 0;
  for (int i = t; i <= n; i++) {
    suma = max(suma, pre[i] - pre[i - t]);
  }

  cout << suma + t * k - t * (t + 1) / 2 << '\n';
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