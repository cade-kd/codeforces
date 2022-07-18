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
  string sa, sb;
  cin >> sa >> sb;

  if (sa[0] != sb[0] || sa.back() != sb.back()) {
    cout << "-1\n";
    return;
  }

  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    a[i] = sa[i] - '0';
    b[i] = sb[i] - '0';
  }

  int cnt = a[0] - b[0];
  for (int i = n - 1; i > 0; i--) {
    a[i] ^= a[i - 1];
    b[i] ^= b[i - 1];
    cnt += a[i] - b[i];
  }

  if (cnt != 0) {
    cout << "-1\n";
    return;
  }


  int64_t ans = 0;
  for (int i = n - 1, j = n - 1;i && j; ) {
    if (a[i] == b[j]) {
      if (a[i]) ans += abs(i - j);
      --i; --j;
      continue;
    }

    if (a[i]) {
      --j;
    }
    else --i;
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