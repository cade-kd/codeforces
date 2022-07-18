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
  vector<int64_t> a(n);
  cin >> a;

  if (a[0] < 0) {
    cout << "NO\n";
    return;
  }

  bool end = a[0] == 0;
  for (int i = 1; i < n; i++) {
    a[i] += a[i - 1];
    if (a[i] < 0 || end && a[i]) {
      cout << "NO\n";
      return;
    }
    if (a[i] == 0) {
      end = true;
    }
  }

  cout << (end ? "YES" : "NO") << "\n";

}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
  // freopen("input.txt", "r", stdin);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}