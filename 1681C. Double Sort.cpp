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
  cin >> n;
  vector<int> a(n), b(n), id(n), pos(n), originalPos(n);
  cin >> a >> b;
  iota(id.begin(), id.end(), 0);
  iota(pos.begin(), pos.end(), 0);
  iota(originalPos.begin(), originalPos.end(), 0);
  //copy(id.begin(), id.end(), pos.begin());

  sort(id.begin(), id.end(), [&](const int i, const int j) {
    if (a[i] < a[j]) return true;
    if (a[i] == a[j] && b[i] < b[j]) return true;
    return false;
    });

  for (int i = 1; i < n; i++) {
    if (b[id[i]] < b[id[i - 1]]) {
      cout << "-1\n";
      return;
    }
  }
  // id: 排在第i的，原先在哪个位置
  // pos: 原来位置i，现在在哪
  // originalPos = pos的逆，当前第i个位置，原先是哪个位置
  vector<array<int, 2>> ans;
  for (int i = 0; i < n; i++) {
    int j = pos[id[i]];
    if (i == j) continue;
    ans.push_back({ i + 1, j + 1 });
    swap(pos[originalPos[i]], pos[originalPos[j]]);
    swap(originalPos[i], originalPos[j]);
  }

  cout << ans.size() << "\n";
  for (array<int, 2> &a : ans) {
    cout << a[0] << " " << a[1] << "\n";
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