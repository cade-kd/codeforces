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
const int INF = 0x3f3f3f3f;
void solve() {
  int n, m;
  cin >> n >> m;
  string t, s;
  cin >> t >> s;

  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
  vector<int> pre(n + 1), suf(n + 1);

  int k = 0;
  for (int i = 1; i <= n; i++) {
    if (k < m && t[i - 1] == s[k]) {
      k++;
    }
    pre[i] = k;
  }
  if (pre[n] != m) {
    cout << "-1\n";
    return;
  }

  k = m - 1;
  for (int i = n; i >= 1; i--) {
    if (k >= 0 && t[i - 1] == s[k]) {
      k--;
    }
    suf[i] = m - 1 - k;
  }

  int ans = INF;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (t[i - 1] != s[j - 1]) continue;
      dp[i][j] = dp[i - 1][j - 1] + 1;

      if (pre[i] < j || suf[i] < m - j + 1) continue;

      if (dp[i][j] == i) {
        ans = min(ans, n - dp[i][j]);
      }
      else {
        ans = min(ans, n - i + 2 * (i - dp[i][j]) - (j - dp[i][j]) + 1);
      }

    }
  }

  cout << min(ans, n) << "\n";

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