#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> match, vis;

bool dfs(int u) {
  if (vis[u]) return 0;
  vis[u] = 1;
  for (auto& v : g[u]) {
    if (match[v] == -1) {
      match[v] = u;
      return 1;
    }
  }
  for (auto& v : g[u]) {
    if (dfs(match[v])) {
      match[v] = u;
      return true;
    }
  }
  return false;
}

void solve() {
  int n, m;
  cin >> n >> m;

  vector<int> x, y;
  for (int i = 0; i < n; i++) {
    int t;
    cin >> t;
    if (3LL * t > m) x.push_back(t);
    else y.push_back(t);
  }

  // 建图
  g.resize(x.size());
  match.resize(y.size(), -1);
  for (int i = 0; i < x.size(); i++) {
    for (int j = 0; j < y.size(); j++) {
      if (x[i] % y[j] == 0 && 2LL * x[i] + y[j] <= m) {
        g[i].push_back(j);
      }
    }
  }

  int cnt = 0;
  vis.resize(x.size());
  for (int i = 0; i < x.size(); i++) {
    vis.assign(x.size(), 0);
    cnt += dfs(i);
  }

  if (cnt < x.size()) {
    cout << "-1\n";
    return;
  }

  cout << y.size() << "\n";
  for (int j = 0; j < y.size(); j++) {
    if (match[j] == -1) {
      cout << 3 * y[j] << " " << 2 * y[j] << "\n";
    }
    else {
      cout << 2 * x[match[j]] + y[j] << " " << x[match[j]] + y[j] << "\n";
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}