#include<bits/stdc++.h>
using namespace std;

void solve() {
  int n, k;
  cin >> n >> k;
  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    mp[a] ++;
  }
  int miss = 0, mex = n;
  for (int i = 0; i <= n; i++) {
    if (mp.count(i) == 0) {
      miss++;
      if (miss > k) {
        --miss;
        mex = i;
        break;
      }
    }
  }

  int diff = mex;

  vector<int> s;
  for (pair<const, int>& entry : mp) {
    if (entry.first < mex) continue;
    diff++;
    s.push_back(entry.second);
  }

  if (s.size() == 0) {
    cout << "0\n";
    return;
  }

  sort(s.begin(), s.end());

  auto iter = s.begin();
  int num = *iter;
  int r = mex == 0 ? 0 : miss;
  while (r-- && iter != s.end()) {
    if (--num == 0) {
      diff--;
      if (r) {
        if (++iter != s.end()) num = *iter;
      }
    }
  }

  cout << diff - mex << "\n";

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