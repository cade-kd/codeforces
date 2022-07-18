#include<bits/stdc++.h>
#include <random>
using namespace std;
void solve() {
  std::uniform_real_distribution<double> distribution(0, 1);
  default_random_engine e;

  int TOTAL = 100000;
  array<double, 3> meet;
  double yprob = 0.006;

  for (int i = 0, cnt = 0; i < TOTAL; i++) {
    int num = 0;
    for (int j = 0; j < 10; j++) {
      if (++cnt > 73) yprob += 0.06;
      if (distribution(e) <= yprob) {
        ++num;
        cnt = 0;
        yprob = 0.006;
      }
    }
    meet[num] += 1;
  }

  cout << meet[0] / TOTAL << " " << meet[1] / TOTAL << " " << meet[2] / TOTAL << endl;
}

signed main() {
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