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
  int a, zcnt = 0, pre = 0, segs = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    if (a == 0) ++zcnt;
    if (a == 0 && pre) ++segs;
    pre = a;
  }

  if (pre) ++segs;

  if (zcnt == n) cout << "0\n";
  else if (segs == 1) cout << "1\n";
  else cout << "2\n";
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