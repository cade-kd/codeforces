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

int MOD = 998244353;
void solve() {
  int n, s;
  cin >> n >> s;
  vector<int> a(n), b(n), pa(n + 1), pb(n + 1, -1);
  cin >> a >> b;

  for (int i = 0; i < n; i++) {
    pa[a[i]] = i;
    if (b[i] != -1)
      pb[b[i]] = i;
  }

  // r就是 >= a[p] - s且还未被使用的数的个数
  int r = 0;
  for (int i = n; i > n - s; i--) {
    if (pb[i] == -1) {
      r++;
    }
  }

  int ans = 1;
  for (int i = n; i >= 1 && ans; i--) {
    if (i > s && pb[i - s] == -1) r++;

    int p = pa[i];
    if (b[p] == -1) {
      ans = 1LL * ans * r % MOD;
      r--;
    }
    else if (i - b[p] > s) {
      ans = 0;
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