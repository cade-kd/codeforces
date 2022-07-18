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

vector<int64_t> split(vector<int>& a, int m) {
  vector<int64_t> s;
  int pre = -1;
  int idx = 0;
  for (int i = 0; i < a.size();i++) {
    int64_t cnt;
    if (a[i] % m) {
      cnt = 1;
    }
    else {
      int64_t t = 1;
      while (a[i] % m == 0) {
        a[i] /= m;
        t *= m;
      }
      cnt = t;
    }

    if (a[i] == pre) {
      s.back() += cnt;
    }
    else {
      s.push_back(cnt);
      a[idx++] = a[i];
      pre = a[i];
    }
  }
  a.resize(s.size());
  return s;

}
void solve() {
  int n, m, k;

  cin >> n >> m;
  vector<int> a(n);
  cin >> a >> k;
  vector<int> b(k);
  cin >> b;

  vector<int64_t> sa = split(a, m);
  vector<int64_t> sb = split(b, m);

  if (a.size() != b.size()) {
    cout << "No\n";
    return;
  }

  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i] || sa[i] != sb[i]) {
      cout << "No\n";
      return;
    }
  }
  cout << "Yes\n";
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