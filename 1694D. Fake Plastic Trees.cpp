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

const int N = 200005;
vector<int> edges[N];

void addEdge(int from, int to) {
  edges[from].push_back(to);
}

int l[N], r[N];

int64_t dfs(int x, int& cnt) {
  int64_t maxVal = 0;
  for (int y : edges[x]) {
    maxVal += dfs(y, cnt);
  }

  if (maxVal < l[x]) {
    cnt++;
    maxVal = r[x];
  }

  return min((int64_t)r[x], maxVal);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) edges[i].clear();
  for (int i = 2; i <= n; i++) {
    int p;
    cin >> p;
    addEdge(p, i);
  }
  for (int i = 1; i <= n; i++) {
    cin >> l[i] >> r[i];
  }
  int ans = 0;
  dfs(1, ans);

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