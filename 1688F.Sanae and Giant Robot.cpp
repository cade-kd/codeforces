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
  int n, m;
  cin >> n >> m;
  vector<int64_t> a(n), b(n), pre(n + 1);
  set<int> unset;
  cin >> a >> b;
  for (int i = 1; i <= n; i++) {
    pre[i] = a[i - 1] - b[i - 1] + pre[i - 1];
    if (pre[i]) unset.insert(i);
  }
  vector<vector<array<int, 2>>> intervals(n + 1);
  queue<array<int, 2>> que;
  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    if (!pre[l - 1] && !pre[r]) {
      que.push({ l, r });
    }
    else {
      intervals[l - 1].push_back({ l , r });
      intervals[r].push_back({ l , r });
    }
  }

  while (!que.empty()) {
    array<int, 2> u = que.front(); que.pop();

    auto iter = unset.lower_bound(u[0]);

    while (iter != unset.end() && *iter <= u[1]) {
      pre[*iter] = 0;
      for (array<int, 2>&ints : intervals[*iter]) {
        if (!pre[ints[0] - 1] && !pre[ints[1]]) {
          que.push({ ints[0], ints[1] });
        }
      }
      unset.erase(iter++);
    }
  }

  if (unset.empty()) {
    cout << "YES\n";
  }
  else {
    cout << "NO\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
  // freopen("input.txt", "r", stdin);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}