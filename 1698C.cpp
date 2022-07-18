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
  vector<int> a;
  int neg = 0, pos = 0, zero = 0;
  for (int i = 0; i < n;i++) {
    int x;
    cin >> x;
    if (x > 0) {
      if (++pos < 3) a.push_back(x);
    }
    else if (x < 0) {
      if (++neg < 3) a.push_back(x);
    }
    else {
      if (++zero == 1)a.push_back(x);
    }
  }

  if (pos >= 3 || neg >= 3) {
    cout << "NO\n";
    return;
  }

  set<int> s;
  for (int x : a) {
    s.insert(x);
  }

  for (int i = 0; i < a.size(); i++) {
    for (int j = i + 1; j < a.size(); j++) {
      for (int k = j + 1; k < a.size(); k++) {
        if (!s.count(a[i] + a[j] + a[k])) {
          cout << "NO\n";
          return;
        }
      }
    }
  }
  cout << "YES\n";

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