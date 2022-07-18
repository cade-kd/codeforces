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
const int MOD = 1e9 + 7;
const int N = 100005;
int fac[N];
bool isInit = false;
void init() {
  if (isInit) return;
  isInit = true;
  fac[0] = 1;
  for (int i = 1;i < N; i++) {
    fac[i] = 1LL * fac[i - 1] * i % MOD;
  }
}

void solve() {
  init();
  int n;
  cin >> n;
  vector<int> a(n), pa(n);
  cin >> a;
  for (int i = 0; i < n; i++) {
    pa[a[i]] = i;
  }

  int left = pa[0], right = pa[0], ans = 1, cnt = 0;
  for (int i = 1; i < n; i++) {
    if (left <= pa[i] && pa[i] <= right) {
      ans = 1LL * ans * cnt % MOD;
      cnt--;
      continue;
    }

    if (pa[i] < left) {
      cnt += left - pa[i] - 1;
      left = pa[i];
    }
    else {
      cnt += pa[i] - right - 1;
      right = pa[i];
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