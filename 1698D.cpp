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

int query(int l, int r) {
  cout << "? " << l << " " << r << endl;
  int a, parity = 0;
  for (int i = l;i <= r;i++) {
    cin >> a;
    if (l <= a && a <= r) parity ^= 1;
  }
  return parity;
}

void solve() {
  int n;
  cin >> n;
  int left = 1, right = n;
  while (left < right) {
    int mid = (left + right) / 2;
    if (query(left, mid))
      right = mid;
    else
      left = mid + 1;
  }
  cout << "! " << left << endl;
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