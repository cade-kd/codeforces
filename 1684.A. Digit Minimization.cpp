#include<bits/stdc++.h>
using namespace std;

void solve() {
  string s; cin >> s;
  if (s.length() == 2) cout << s[1] << '\n';
  else cout << *min_element(s.begin(), s.end()) << '\n';
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