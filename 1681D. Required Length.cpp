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
int n, ans;
int cnt[10];
int dfs(uint64_t x, int depth) {

  uint64_t y = x;
  int bcnt = 1;
  vector<int> cnt(10);
  cnt[y % 10]++;
  while (y /= 10) {
    bcnt++;
    cnt[y % 10]++;
  }

  if (bcnt >= n) {
    return ans = min(ans, depth);
  }

  if (depth + n - bcnt >= ans) {
    return ans;
  }

  int t = ans;
  for (int i = 9; i > 1; i--) {
    if (cnt[i]) {
      t = min(t, dfs(x * i, depth + 1));
    }
  }
  return t;
}

void solve() {
  uint64_t x;
  cin >> n >> x;
  uint64_t y = x;
  int cnt = 1, zcnt = y % 10;
  while (y /= 10) {
    cnt++;
    zcnt += y % 10;
  }

  if (cnt == n) { cout << "0\n"; return; }
  else if (cnt > n) {
    if (zcnt && n == 1)  cout << "1\n";
    else cout << "-1\n";
    return;
  }
  ans = 100;
  dfs(x, 0);
  if (ans == 100) ans = -1;

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