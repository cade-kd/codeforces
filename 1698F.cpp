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
  vector<int> a(n), b(n);
  cin >> a >> b;

  if (a[0] != b[0] || a.back() != b.back()) {
    cout << "NO\n";
    return;
  }
  vector<pair<int, int>> ans;
  // 可以做一些常数上的优化，但是我懒得写
  for (int i = 1; i < n - 1; i++) {
    if (a[i] == b[i]) continue;
    int pos = 0;
    // 情况1
    for (int j = i + 1; j < n; j++) {
      if (a[j] == a[i - 1] && a[j - 1] == b[i]) {
        pos = j;
        break;
      }
    }

    // 情况2
    int t = 0;
    for (int j = i; j < n - 1 && !pos; j++) {
      for (int k = j + 1; k < n && !pos; k++) {
        if (a[j] != a[k]) continue;
        t = max(t, j);
        for (; t < k; t++) {
          if (a[t] == a[i - 1] && a[t + 1] == b[i]) {
            reverse(&a[j], &a[k] + 1);
            ans.push_back({ j, k });
            pos = j + k - t;
            break;
          }
        }
      }
    }

    if (pos) {
      reverse(&a[i - 1], &a[pos] + 1);
      ans.push_back({ i - 1, pos });
    }
    else {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
  cout << ans.size() << "\n";
  for (auto [x, y] : ans) {
    cout << x + 1 << " " << y + 1 << "\n";
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