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

const int N = 100003;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  cin >> a;
  int minIdx = min_element(a.begin(), a.end()) - a.begin();
  vector<int> lmin(n), lmax(n), rmin(n), rmax(n);

  lmin[0] = rmin[0] = 0;
  for (int i = 1;i < n;i++) {
    if (a[i] < a[lmin[i - 1]]) lmin[i] = i;
    else lmin[i] = lmin[i - 1];

    if (a[i] > a[lmax[i - 1]]) lmax[i] = i;
    else lmax[i] = lmax[i - 1];
  }
  rmin[n - 1] = rmax[n - 1] = n - 1;
  for (int i = n - 2;i >= 0;i--) {
    if (a[i] < a[rmin[i + 1]]) rmin[i] = i;
    else rmin[i] = rmin[i + 1];

    if (a[i] > a[rmax[i + 1]]) rmax[i] = i;
    else rmax[i] = rmax[i + 1];
  }

  int id = minIdx;
  int ans = 0;
  while (id) {
    id = lmax[id];
    ++ans;
    if (id == 0) break;
    id = lmin[id];
    ++ans;
  }

  id = minIdx;
  while (id != n - 1) {
    id = rmax[id];
    ++ans;
    if (id == n - 1) break;
    id = rmin[id];
    ++ans;
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
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}