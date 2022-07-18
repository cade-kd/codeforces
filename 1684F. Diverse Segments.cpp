#include<bits/stdc++.h>
using namespace std;
const int N = 200005;
int pre[N], a[N], nx[N], maxR[N];
void solve() {
  int n, m;
  cin >> n >> m;
  map<int, vector<int>> pos;
  memset(pre, -1, sizeof(int) * (n + 1));
  memset(nx, -1, sizeof(nx));
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (pos.count(a[i])) {
      pre[i] = pos[a[i]].back();
      nx[pos[a[i]].back()] = i;
    }
    pos[a[i]].push_back(i);
  }

  memset(maxR, -1, sizeof(int) * n);
  for (int i = 0; i < m; i++) {
    int L, R;
    cin >> L >> R;
    maxR[L - 1] = max(maxR[L - 1], R - 1);
  }

  for (int i = 1; i < n; i++) {
    maxR[i] = max(maxR[i], maxR[i - 1]);
  }

  int l = 0, r = n - 1;
  for (int i = n - 2; i >= -1; i--) {
    if (nx[i + 1] == -1 || maxR[i + 1] < nx[i + 1]) {
      r = i;
    }
    else break;
  }

  if (r == -1) {
    cout << "0\n";
    return;
  }

  int ans = r - l + 1;
  while (++l < n) {
    if (pre[l - 1] != -1 && maxR[pre[l - 1]] >= l - 1) {
      break;
    }
    vector<int>& p = pos[a[l - 1]];
    auto iter = upper_bound(p.begin(), p.end(), r);
    if (iter != p.end() && maxR[l - 1] >= *iter) {
      r = *iter;
    }
    ans = min(ans, r - l + 1);
  }
  cout << ans << "\n";

}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}