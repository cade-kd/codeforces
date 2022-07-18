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
  int  n, m;
  cin >> n >> m;
  vector<int> a(n + 1);
  for (int i = 1;i <= m;i++) {
    int x;
    cin >> x;
    a[x]++;
  }
  auto check = [&](int t) {
    int64_t r = m;
    for (int i = 1;i <= n;i++) {
      if (a[i] < t) r -= a[i] + (t - a[i]) / 2;
      else r -= t;
    }
    return r <= 0;
  };

  int l = 1, r = 2 * m;
  while (l < r) {
    int mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }

  cout << l << "\n";
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