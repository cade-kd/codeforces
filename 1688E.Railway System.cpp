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

template<typename T>
ostream& operator<<(ostream& outs,
  vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) outs << v[i] << " ";
  return outs;
}

template<>
ostream& operator<<(ostream& outs,
  vector<char>& v) {
  for (int i = 0; i < int(v.size()); i++) outs << v[i];
  return outs;
}

int query(vector<char> s) {
  cout << "? " << s << endl;
  int res;
  cin >> res;
  return res;
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector q(m, '0');

  vector<array<int, 2>> edges(m);

  for (int i = 0;i < m;i++) {
    q[i] = '1';
    int w = query(q);
    edges[i] = { w, i };
    q[i] = '0';
  }

  sort(edges.begin(), edges.end());

  int minWeights = 0;
  for (const array<int, 2> &u : edges) {
    q[u[1]] = '1';
    int w = query(q);

    if (w == minWeights + u[0]) {
      minWeights = w;
    }
    else {
      q[u[1]] = '0';
    }
  }
  cout << "! " << minWeights << endl;
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