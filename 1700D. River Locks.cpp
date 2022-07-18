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
const int N = 200005;
int v[N];
int64_t p[N];
void solve() {
  int n;
  cin >> n;
  p[0] = 0;
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
    p[i] = p[i - 1] + v[i];
  }
  int64_t least = 1e15;
  int64_t left = 1, right = 1e15;
  while (left <= right) {
    int64_t mid = (left + right) / 2;
    int64_t sum = 0;
    bool success = true;
    for (int i = 1; i <= n; i++) {
      if (sum <= 1e15)
        sum += mid;
      if (sum < p[i]) {
        success = false;
        break;
      }
    }
    if (success) {
      right = mid - 1;
      least = mid;
    }
    else {
      left = mid + 1;
    }
  }
  int q;
  cin >> q;
  while (q--) {
    int tj;
    cin >> tj;
    if (tj < least) {
      cout << "-1\n";
      continue;
    }
    int64_t ans = (p[n] + tj - 1) / tj;
    cout << ans << "\n";
  }
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