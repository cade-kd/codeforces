#include<bits/stdc++.h>
using namespace std;
template<typename T>
istream& operator>>(istream& ins,
  vector<T>& v) {
  for (int i = 0; i < int(v.size()); i++) ins >> v[i];
  return ins;
}

void solve() {
  int n;
  string s;
  cin >> n >> s;
  int oneCnt = 0;
  for (int i = 0; i < n; i++) {
    oneCnt += s[i] - '0';
  }
  if (oneCnt & 1 || oneCnt == 0) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  int pos = s.find('1');
  int last = s.find_last_of('1');

  int pre = pos;
  for (int i = pos + 1; i != last; i++) {
    if (s[i] == '1') {
      cout << pre + 1 << " " << i + 1 << "\n";
      pre = pos;
    }
    else {
      cout << pre + 1 << " " << i + 1 << "\n";
      pre = i;
    }
  }
  for (int i = (pos - 1 + n) % n; i != last - 1; i = (i + n - 1) % n) {
    cout << pre + 1 << " " << i + 1 << "\n";
    pre = i;
  }
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