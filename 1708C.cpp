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

// void solve() {
//   int n, q;
//   cin >> n >> q;
//   vector<int> a(n), d(n);
//   cin >> a;

//   d[n - 1] = 1;
//   for (int i = n - 2; i >= 0; i--) {
//     d[i] = d[i + 1];
//     if (a[i] > d[i + 1]) ++d[i];
//   }

//   vector<char> ans(n, '1');
//   for (int i = 0; i < n && q < d[i]; i++) {
//     if (a[i] > q) ans[i] = '0';
//   }
//   cout << string(ans.begin(), ans.end()) << "\n";

// }

bool checkAndFill(const vector<int>& a, const int q, const int x, vector<int>& ans) {
  int n = a.size();
  ans.assign(n, 0);
  int d = 0, cnt = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (a[i] <= d) {
      ++cnt;
      ans[i] = 1;
    }
    else if (d < q) {
      ++d;
      ++cnt;
      ans[i] = 1;
    }
  }
  return cnt >= x;
}

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  cin >> a;
  vector<int> ans;
  int l = min(q, n), r = n;
  while (l <= r) {
    int x = (l + r) / 2;

    if (checkAndFill(a, q, x, ans)) {
      l = x + 1;
    }
    else {
      r = x - 1;
    }
  }

  checkAndFill(a, q, l - 1, ans);

  for (int i = 0; i < n; i++) cout << ans[i];
  cout << "\n";
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