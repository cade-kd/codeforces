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
  int n, c, q;
  string s;
  cin >> n >> c >> q >> s;
  vector<int64_t> l(c);
  vector<int64_t> r(c);
  vector<int64_t> lens(c + 1);
  lens[0] = n;
  for (int i = 0; i < c; i++) {
    cin >> l[i] >> r[i];
    lens[i + 1] = r[i] - l[i] + 1;
  }
  for (int i = 1; i <= c; i++) lens[i] += lens[i - 1];

  while (q--) {
    int64_t x;
    cin >> x;

    for (int i = c; i >= 1; i--) {
      if (x > lens[i - 1]) {
        x = l[i - 1] + x - lens[i - 1] - 1;
      }
    }

    cout << s[x - 1] << "\n";
  }
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