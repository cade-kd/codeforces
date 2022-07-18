#include<bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif

  int t;
  for (cin >> t; t; t--) {
    int n;
    cin >> n;
    const int INF = 1e9;
    vector<int> A(n + 2);

    for (int i = 1; i <= n; i++) {
      cin >> A[i];
      --A[i];
    }
    bool comb[n + 2][n + 2]{};
    for (int i = 0; i <= n; i++) {
      vector<int> cnt(n);
      for (int j = i + 1, mx = 0; j <= n + 1; j++) {
        // if (i == 2 && j == 5) cout << ((j-i) & 1) << (mx <= (j - i - 1) / 2) << (A[i]==A[j]) << '\n';
        if ((j - i) & 1 && mx <= (j - i - 1) / 2 && (i == 0 or j == n + 1 or A[i] == A[j]))
          comb[i][j] = 1;
        mx = max(mx, ++cnt[A[j]]);
      }
    }
    // for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) cout << comb[i][j] << " \n"[j == n];
    vector<int> dp(n + 2, -INF);
    dp[0] = 0;
    for (int i = 0; i <= n; i++) {
      for (int j = i; j <= n + 1; j++) {
        if (comb[i][j]) dp[j] = max(dp[j], 1 + dp[i]);
      }
    }
    cout << dp[n + 1] - 1 << '\n';
  }
  return 0;
}