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
const int N = 205000;
vector<int> edges[N];


int cnt[N];

int dfs1(int x, int fa) {
  int ret = 0;
  for (int i = 0; i < edges[x].size(); i++) {
    int y = edges[x][i];
    if (y == fa) continue;
    int res = dfs1(y, x);
    if (!res) ++cnt[x];
    else ret += res;
  }

  if (cnt[x]) {
    ret += cnt[x] - 1;
  }

  return ret;
}

/**
 * @brief 换根dp
 *
 * @param x
 * @param fa
 * @param ans
 */
void dfs2(int x, int fa, int& ans, int& cur) {
  int pre = cur, cntfa = cnt[fa], cntx = cnt[x];
  if (!fa) ans = cur = dfs1(x, fa);
  else {
    if (cnt[x] == 1 && edges[x].size() == 2
      || edges[x].size() == 1) {
      if (cnt[fa]-- >= 2) cur--;
    }

    if (cnt[fa] == 1 && edges[fa].size() == 2
      || edges[fa].size() == 1) {
      if (cnt[x]++ >= 1) cur++;
    }

    ans = min(ans, cur);
  }


  for (int y : edges[x]) {
    if (y == fa) continue;
    dfs2(y, x, ans, cur);
  }

  //恢复
  cnt[fa] = cntfa;
  cnt[x] = cntx;
  cur = pre;
}

void init(int n) {
  for (int i = 1; i <= n; i++) {
    edges[i].clear();
  }
}
void solve() {

  int n;
  cin >> n;
  init(n);

  for (int i = 1; i < n; i++) {
    int x, y;
    cin >> x >> y;
    edges[x].push_back(y);
    edges[y].push_back(x);
  }

  if (n == 1) {
    cout << "0\n";
    return;
  }


  int ans = n + 1, cur = n + 1;

  memset(cnt, 0, (n + 1) * sizeof * cnt);
  dfs2(1, 0, ans, cur);

  cout << ans + 1 << "\n";
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