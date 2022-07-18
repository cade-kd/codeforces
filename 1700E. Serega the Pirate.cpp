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

const int N = 400005;
int a[N], n, m;

bool valid(int pos, int nx) {
  if (nx < 0 || nx >= n * m || nx / m != pos / m && nx % m != pos % m)
    return false;
  return true;
}
bool check(int pos) {
  if (a[pos] == 1) return true;
  vector<int> offset = { -1, +1, -m, +m };
  for (int off : offset) {
    int nx = pos + off;
    if (valid(pos, nx) && a[nx] < a[pos]) return true;
  }
  return false;
}
void solve() {
  cin >> n >> m;

  for (int i = 0; i < n * m; i++) {
    cin >> a[i];
  }
  vector<int> badPos;
  for (int i = 0; i < n * m; i++) {
    if (!check(i)) {
      badPos.push_back(i);
    }
  }

  if (badPos.size() == 0) {
    cout << 0 << endl;
    return;
  }
  if (badPos.size() > 5) {
    cout << 2 << endl;
    return;
  }

  vector<int> cand, vis(n * m);
  int k = badPos[0];
  cand.push_back(k);
  vis[k] = 1;

  vector<int> offset = { -1, +1, -m, +m };
  for (int off : offset) {
    int nx = k + off;
    if (valid(k, nx)) {
      cand.push_back(nx);
      vis[nx] = 1;
    }
  }

  int cnt = 0;
  for (int pos : cand) {
    for (int i = 0; i < n * m; i++) {
      if (vis[i] && pos >= i) continue;

      swap(a[pos], a[i]);

      bool success = check(i) && check(pos);
      for (int b : badPos) {
        success &= check(b);
      }

      for (int off : offset) {
        int nx = pos + off;
        if (success && valid(pos, nx) && !check(nx)) success = false;
        nx = i + off;
        if (success && valid(i, nx) && !check(nx)) success = false;
      }

      swap(a[pos], a[i]);

      if (success) cnt++;
    }
  }

  if (cnt)
    cout << 1 << " " << cnt << endl;
  else cout << 2 << endl;
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