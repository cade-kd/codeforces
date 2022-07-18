#include<bits/stdc++.h>
using namespace std;
#define LOCAL
template<typename T>
istream& operator>>(istream& ins,
  vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) ins >> v[i];
  return ins;
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  cin >> a;
  int once = 0, twice = 0;
  sort(a.begin(), a.end());
  for (int i = 0, j = 1; i < n; i = j++) {
    while (j < n && a[j] == a[j - 1]) j++;
    if (j - i > 1) twice++;
    else once++;
  }

  cout << twice + (once + 1) / 2 << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
#endif
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}