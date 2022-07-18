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

template<class T = int>
class FenwickTree {
  int n, sum;
  vector<T> c;
public:
  FenwickTree() :n(-1) {}
  FenwickTree(int n) :n(n), c(n + 2), sum(0) {}

  void reset(int n) {
    this->n = n;
    c.resize(n + 2, 0);
    sum = 0;
  }

  inline int lowbit(int x) {
    return x & (-x);
  }

  void add(int i, T k) {
    if (i <= n)
      sum = sum + k;
    while (i <= n) {
      c[i] = c[i] + k;
      i += lowbit(i);
    }
  }
  // 区间加上k
  void addInt(int l, int r, T k) {
    assert(l <= r);
    add(l, k);
    add(r + 1, -k);
  }

  T preSum(int i) {
    T res = 0;
    while (i > 0) {
      res = res + c[i];
      i -= lowbit(i);
    }
    return res;
  }

  T sufSum(int i) {
    return sum - preSum(i - 1);
  }
  //区间[a,b]的和
  T intSum(int a, int b) {
    return preSum(b) - preSum(a - 1);
  }
};

struct DisjointSetUnion {
  int n;
  vector<int> pa, dep;

  DisjointSetUnion(int n = 0) :n(n), pa(n + 1), dep(n + 1) {}

  void reset(int n) {
    this->n = n;
    pa.resize(n + 1, 0);
    dep.resize(n + 1, 0);
  }

  int findpa(int x) {
    assert(x && x <= n);
    return pa[x] ? pa[x] = findpa(pa[x]) : x;
  }

  bool unite(int a, int b) {
    a = findpa(a);
    b = findpa(b);
    if (a == b) return false;
    if (dep[a] > dep[b])
      pa[b] = a;
    else {
      pa[a] = b;
      if (dep[a] == dep[b]) ++dep[b];
    }
    return true;
  }
} dsu;

FenwickTree<int> bit;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<pair<int, int>> edges(m);
  vector<int> used(m);
  vector<vector<int>> tree(n + 1);

  dsu.reset(n);
  bit.reset(n);
  int nonTreeEdgeCnt = m;
  for (int i = 0; i < m;i++) {
    int u, v;
    cin >> u >> v;
    edges[i] = { u, v };
    used[i] = dsu.unite(u, v);
    if (used[i]) {
      nonTreeEdgeCnt--;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }
  }

  vector<int> du(n + 1), out(n + 1);
  int cnt = 0;
  function<void(int, int)> dfs = [&](int x, int fa) -> void {
    du[x] = ++cnt;
    for (int y : tree[x]) {
      if (y == fa) continue;
      dfs(y, x);
    }
    out[x] = cnt;
  };

  dfs(1, 0);

  for (int i = 0; i < m; i++) {
    if (used[i]) continue;
    auto [u, v] = edges[i];
    if (du[u] > du[v]) swap(u, v);
    // v是u的子树节点
    if (du[v] <= out[u]) {
      int l = 0, r = tree[u].size() - 1;
      int ch = -1;
      while (l < r) {
        if (du[tree[u][l]] < du[u]) ++l;
        if (du[tree[u][r]] < du[u]) --r;
        assert(l <= r);
        int mid = (l + r) / 2;
        if (du[tree[u][mid]] < du[u]) --mid;
        assert(mid >= l);
        if (du[tree[u][mid]] <= du[v]
          && du[v] <= out[tree[u][mid]]) {
          ch = tree[u][mid];
          break;
        }

        if (out[tree[u][mid]] < du[v]) {
          l = mid + 1;
        }
        else {
          r = mid;
        }
      }
      if (ch == -1) ch = tree[u][r];
      bit.addInt(1, n, 1);
      bit.addInt(du[ch], out[ch], -1);
      bit.addInt(du[v], out[v], 1);
    }
    else {
      bit.addInt(du[u], out[u], 1);
      bit.addInt(du[v], out[v], 1);
    }
  }
  string ans;
  for (int i = 1; i <= n; i++) {
    if (bit.preSum(du[i]) == nonTreeEdgeCnt) ans += '1';
    else ans += '0';
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
  // cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}