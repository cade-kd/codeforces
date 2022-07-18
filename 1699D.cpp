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

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  cin >> a;
  vector<vector<int>> num(n + 1);
  for (int i = 0; i < n; i++) {
    num[a[i]].push_back(i);
  }

  vector<int> cnt(n + 1);
  vector<vector<int>> graph(n + 1),
    canEleminate(n + 1, vector<int>(n + 1));
  for (int i = 0; i < n - 1; i++) {
    int maxCnt = 1, maxVal = a[i];
    fill(cnt.begin(), cnt.end(), 0);
    cnt[a[i]] = 1;
    for (int j = i + 1; j < n; j++) {
      cnt[a[j]]++;
      if (a[j] == maxVal) ++maxCnt;
      else if (maxCnt == 0) {
        maxCnt = 1;
        maxVal = a[j];
      }
      else {
        maxCnt--;
      }

      if (((j - i) & 1) && cnt[maxVal] <= (j - i + 1) / 2) {
        canEleminate[i][j] = 1;
      }
    }
  }

  vector<int> degree(n + 1);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (num[i].size() <= 1) continue;

    for (int j = 0; j < num[i].size(); j++) {
      int numa = num[i][j];
      if (degree[numa] == 0 && !canEleminate[0][numa - 1]) {
        continue;
      }
      for (int k = j + 1; k < num[i].size(); k++) {
        int numb = num[i][k];
        if (numb == numa + 1 || canEleminate[numa + 1][numb - 1]) {
          graph[numa].push_back(numb);
          degree[numb]++;
        }
      }
    }
  }

  queue<int> que;

  vector<int> dist(n + 1);
  for (int i = 0; i < n; i++) {
    if (degree[i] == 0 &&
      (i == 0 || canEleminate[0][i - 1])) {
      que.push(i);
      dist[i] = 1;
    }
  }

  while (!que.empty()) {
    int x = que.front(); que.pop();
    if (x == n - 1 || canEleminate[x + 1][n - 1])
      ans = max(ans, dist[x]);
    for (int y : graph[x]) {
      dist[y] = max(dist[y], dist[x] + 1);
      if (--degree[y] == 0) {
        que.push(y);
      }
    }
  }
  cout << ans << endl;

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