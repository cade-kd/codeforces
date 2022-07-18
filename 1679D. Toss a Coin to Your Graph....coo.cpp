#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <queue>
#include <array>
#include <cmath>
#include <limits>
using namespace std;
const int N = 200005;
int a[N], d[N], len[N];
vector<int> graph[N];

bool check(const int n, const int limit, const int64_t k,
  const vector<array<int, 2>>& edges) {
  memset(d, 0, sizeof(d));

  for (auto& e : edges) {
    if (a[e[0]] <= limit && a[e[1]] <= limit) {
      d[e[1]]++;
    }
  }
  memset(len, 0, sizeof(len));
  queue<int> que;
  int total = n;
  for (int i = 1; i <= n; i++) {
    if (a[i] > limit) {
      assert(d[i] == 0);
    }
  }
  for (int i = 1; i <= n; ++i) {
    if (d[i] == 0) {
      if (a[i] <= limit) {
        len[i] = 1;
        que.push(i);
      }
      else --total;
    }
  }
  if (total == 0) return false;
  int maxlen = 1;
  while (!que.empty()) {
    --total;
    int u = que.front();
    int l = len[u];
    maxlen = max(maxlen, l);
    que.pop();
    for (auto v : graph[u]) {
      if (a[v] > limit) continue;
      len[v] = max(len[v], l + 1);
      if (--d[v] == 0) {
        que.push(v);
      }
    }
  }

  if (total != 0 || maxlen >= k) return true;
  return false;
}

void solve() {

  int n, m;
  int64_t k;
  cin >> n >> m >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  vector<array<int, 2>> edges;
  for (int j = 0; j < m; j++) {
    int u, v;
    cin >> u >> v;
    graph[v].push_back(u);
    edges.push_back({ v, u });
  }
  const int UPPERBOUND = 1e9;
  int left = 1, right = UPPERBOUND;

  while (left <= right) {
    int mid = (left + right) >> 1;
    if (check(n, mid, k, edges)) {
      right = mid - 1;
    }
    else {
      left = mid + 1;
    }
  }
  right++;
  if (right > UPPERBOUND) right = -1;
  cout << right << endl;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

}