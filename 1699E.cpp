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
const int M = 5000005;
int  cnt[M], dp[M];
bool a[M];
void solve() {
  int n, m;
  cin >> n >> m;

  memset(a, 0, (m + 1) * sizeof * a);
  int vmax = 0, vmin = INF;

  for (int i = 0; i < n;i++) {
    int x;
    cin >> x;
    a[x] = 1;
    vmax = max(x, vmax);
    vmin = min(x, vmin);
  }

  // 全部数都一样，特判
  if (vmin == vmax) {
    cout << "0\n";
    return;
  }

  memset(dp, 0x3f, (vmax + 1) * sizeof * dp);
  memset(cnt, 0, (vmax + 1) * sizeof * cnt);

  int sqvmax = sqrt(vmax);

  for (int j = sqvmax + 1; j <= vmax; j++) {
    dp[j] = j;
    if (a[j]) {
      cnt[j]++;
    }
  }

  int maxDp = vmax;
  int ans = vmax - vmin;
  for (int j = sqvmax; j >= 1; j--) {
    dp[j] = j;

    if (a[j]) {
      cnt[j]++;
    }

    for (int i = j * j; i <= vmax; i += j) {

      if (dp[i / j] < dp[i]) {
        if (a[i]) cnt[dp[i]]--;
        dp[i] = dp[i / j];
        if (a[i])cnt[dp[i]]++;
      }
    }

    if (j <= vmin) {
      while (cnt[maxDp] == 0) maxDp--;
      ans = min(ans, maxDp - j);
    }
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