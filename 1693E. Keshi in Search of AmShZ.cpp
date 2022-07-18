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

const int N = 200005, INF = 0x3f3f3f3f;
vector<int> edges[N];
int degree[N], dist[N], vis[N];

void addEdge(int from, int to) {
  edges[from].push_back(to);
  degree[to]++;
}

typedef pair<int, int> intpair;

void Dijkstra(int n) {
  priority_queue<intpair,
    vector<intpair>,
    greater<intpair> > que;
  memset(vis, 0, sizeof(vis));
  memset(dist, 0x3f, sizeof(dist));

  dist[n] = 0;
  que.push({ 0, n });
  while (!que.empty()) {
    auto [d, u] = que.top();que.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (int v : edges[u]) {
      if (d + degree[v] < dist[v]) {
        dist[v] = d + degree[v];
        que.push({ dist[v], v });
      }
      degree[v]--;
    }
  }
}

void solve() {

  memset(degree, 0, sizeof(degree));
  int n, m;
  cin >> n >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    addEdge(v, u);
  }

  Dijkstra(n);
  cout << dist[1] << "\n";

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