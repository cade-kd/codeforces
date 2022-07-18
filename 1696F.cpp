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
const int N = 101;
bool eq[N][N][N];
int depth[N], n;

// 获取深度
void dfs(int x, int fa, int dep, vector<vector<int>>& g) {
  depth[x] = dep;
  for (int y : g[x]) {
    if (y == fa) continue;
    dfs(y, x, dep + 1, g);
  }
}

bool check(vector<vector<int>>& g) {
  int n = g.size();
  bool ok = true;
  for (int k = 0; k < n && ok; k++) {
    memset(depth, -1, sizeof(depth));
    dfs(k, -1, 0, g);
    for (int i = 0; i < n && ok; i++) {
      if (depth[i] == -1) {
        ok = false;
      }
      for (int j = i + 1; j < n && ok; j++) {
        if ((depth[i] == depth[j]) != eq[k][i][j]) {
          ok = false;
        }
      }
    }
  }
  return ok;
}

void solve() {
  cin >> n;
  if (n == 1) {
    cout << "Yes\n1\n";
    return;
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = 0; k < n; k++) {
        char ch;
        cin >> ch;
        eq[k][i][j] = eq[k][j][i] = (ch == '1');
      }
    }
  }

  // 枚举和0连接的点
  for (int i = 1; i < n; i++) {
    // 构造的树
    vector<vector<int>> g(n);
    g[0].push_back(i);
    g[i].push_back(0);
    //记录父亲（除了0）
    vector<int> pa(n, -1);
    pa[i] = 0; pa[0] = i;
    queue<int> que;
    que.push(0);
    que.push(i);
    // 构造树
    while (!que.empty()) {
      int u = que.front(); que.pop();
      for (int v = 1; v < n; v++) {
        if (pa[v] != -1 || !eq[u][v][pa[u]]) continue;
        que.push(v);
        pa[v] = u;
        g[u].push_back(v);
        g[v].push_back(u);
      }
    }

    if (check(g)) {
      cout << "Yes\n";
      for (int i = 0; i < n; i++) {
        for (int j : g[i]) {
          if (i >= j) continue;
          cout << i + 1 << " " << j + 1 << "\n";
        }
      }

      return;
    }
  }

  cout << "No\n";
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