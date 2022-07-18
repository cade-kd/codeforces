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
  vector<int> p(n + 1);
  vector<array<int, 2>> dp(n + 1);
  for (int i = 1; i <= n; i++)
    cin >> p[i];

  int64_t ans = 0;
  int last = n + 1;
  for (int i = n; i > 0; i--) {
    dp[i][0] = n + 1; //INF
    dp[i][1] = 0;  // -INF
    for (int j = i + 1; j <= n; j++) {
      int dp0 = 0, dp1 = n + 1;
      if (dp[j - 1][1] < p[j])
        dp0 = max(dp0, p[j - 1]);
      if (p[j - 1] < p[j])
        dp0 = max(dp0, dp[j - 1][0]);

      if (p[j] < dp[j - 1][0])
        dp1 = min(dp1, p[j - 1]);
      if (p[j - 1] > p[j])
        dp1 = min(dp1, dp[j - 1][1]);

      if (dp0 == dp[j][0] && dp1 == dp[j][1]) {
        break;
      }
      dp[j][0] = dp0; dp[j][1] = dp1;
      if (dp0 == 0 && dp1 == n + 1) {
        last = j;
        break;
      }
    }

    ans += last - i;
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
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}