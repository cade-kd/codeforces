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
  int n, m;
  cin >> n >> m;
  vector<vector<int>> a(n + 1, vector<int>(m + 1)),
    maxval(n + 1, vector<int>(m + 1, -1e7)),
    minval(n + 1, vector<int>(m + 1, 1e7));

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      cin >> a[i][j];
    }
  }

  if ((n + m - 1) & 1) {
    return cout << "NO\n", void(0);
  }

  maxval[0][1] = maxval[1][0] = minval[0][1] = minval[1][0] = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      maxval[i][j] = max(maxval[i][j - 1], maxval[i - 1][j]) + a[i][j];
      minval[i][j] = min(minval[i][j - 1], minval[i - 1][j]) + a[i][j];
    }
  }

  if (minval[n][m] <= 0 && maxval[n][m] >= 0) cout << "YES\n";
  else cout << "NO\n";
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