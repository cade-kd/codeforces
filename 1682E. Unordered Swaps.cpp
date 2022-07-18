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
  vector<int> p(n + 1);
  for (int i = 1; i <= n; i++) cin >> p[i];

  vector<vector<pair<int, int>>> g1(n + 1);

  for (int i = 1;i <= m; i++) {
    int u, v;
    cin >> u >> v;
    g1[u].push_back({ i, v });
    g1[v].push_back({ i, u });
  }
  vector<int> vis(n + 1), pos(n + 1);

  // 分每个环分别dfs/bfs更快，因为不同环不会互相影响。
  vector<int> degree(m + 1);
  vector<vector<int>> g(m + 1);
  for (int i = 1; i <= n; i++) {
    if (vis[i]) continue;
    vis[i] = 1;
    vector<int> curLoop;
    curLoop.push_back(i);
    int nx = i;
    for (int j = 1; p[nx] != i; j++) {
      nx = p[nx];
      vis[nx] = 1;
      pos[nx] = j;
      curLoop.push_back(nx);
    }

    const int lpsz = curLoop.size();

    vector<int> e;

    for (int j = 0; j < lpsz; j++) {
      int u = curLoop[j];
      // 逆时针排序
      sort(g1[u].begin(), g1[u].end(),
        [&](const pair<int, int>& a, const pair<int, int>& b) {
          const int& x = a.second, & y = b.second;
          return (pos[x] - j + lpsz) % lpsz
            < (pos[y] - j + lpsz) % lpsz;
        });

      // 记录所有可能度为0的边
      if (g1[u].size()) e.push_back(g1[u][0].first);
      // 建图
      for (int k = 1; k < g1[u].size(); k++) {
        g[g1[u][k - 1].first].push_back(g1[u][k].first);
        degree[g1[u][k].first]++;
      }
    }

    // 拓扑排序，bfs。反向建图dfs也行
    queue<int> que;
    for (int i = 0; i < e.size(); i++) {
      if (degree[e[i]] == 0) {
        que.push(e[i]);
        degree[e[i]] = -1;
      }
    }
    while (!que.empty()) {
      int u = que.front(); que.pop();
      cout << u << " ";

      for (int v : g[u]) {
        if (--degree[v] == 0) {
          que.push(v);
        }
      }
    }
  }

  cout << endl;

}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif
  int t = 1;
  //cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}