#include<bits/stdc++.h>
using namespace std;
// #define LOCAL

void solve() {
  int n;
  string s;
  cin >> n >> s;
  int x = n / 2;
  int ans = 0;
  for (int i = x; i >= 0; i--) {
    if (s[i] == s[x]) ++ans;
    else break;
  }

  for (int i = x + 1; x < n; i++) {
    if (s[i] == s[x]) ++ans;
    else break;
  }

  cout << ans << endl;
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