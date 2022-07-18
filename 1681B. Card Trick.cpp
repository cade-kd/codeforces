#include<bits/stdc++.h>
using namespace std;
template<typename T>
istream& operator>>(istream& ins,
  vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) ins >> v[i];
  return ins;
}

void solve() {
  int n, m;
  cin >> n;
  vector<int> a(n);
  cin >> a;
  cin >> m;
  vector<int> b(m);
  cin >> b;
  int pos = accumulate(b.begin(), b.end(), 0LL) % n;
  cout << a[pos] << "\n";

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