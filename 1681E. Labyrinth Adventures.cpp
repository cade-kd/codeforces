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
const int N = 100005;
const int M = 18;
int64_t dp[N][M][2][2];

int getNormalDist(const array<int, 2>& a, const array<int, 2>& b) {
  int lya = max(a[0], a[1]), lyb = max(b[0], b[1]);
  assert(lya == lyb);
  if (a[0] == b[0] || a[1] == b[1]) return abs(a[0] + a[1] - b[0] - b[1]);

  return 4 * lya - a[0] - a[1] - b[0] - b[1];
}

// dir: 0向上，1向右
// a是一个普通位置，b是一个door
int getdist(const array<int, 2>& a, array<int, 2> b, int dir) {
  // 获得所在的层
  int ly1 = max(a[0], a[1]), ly2 = max(b[0], b[1]);
  if (ly1 == ly2) return getNormalDist(a, b);
  assert(ly1 == ly2 + 1);
  b[dir]++;
  return getNormalDist(a, b) + 1;
}

void solve() {
  int n;
  cin >> n;
  vector<array<array<int, 2>, 2>> door(n - 1), dist(n - 1);

  // 变成从0开始
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j <= 1;j++) {
      for (int k = 0; k <= 1; k++) {
        cin >> door[i][j][k];
        door[i][j][k]--;
      }
    }
  }

  // 预先求出dist
  for (int i = 0; i < n - 1; i++) {
    int s = 4 * (i + 1);
    for (int k1 = 0; k1 <= 1; k1++) {
      for (int k2 = 0; k2 <= 1; k2++) {
        s -= door[i][k1][k2];
      }
    }
    dist[i][0][1] = dist[i][1][0] = s;
  }

  memset(dp, 0x3f, sizeof(dp));

  for (int i = n - 3; i >= 0; --i) {
    for (int k1 = 0; k1 <= 1; k1++) {
      for (int k2 = 0; k2 <= 1; k2++) {
        dp[i][0][k1][k2] = getdist(door[i + 1][k2], door[i][k1], k1);
      }
    }

    for (int j = 1; j < M; j++) {
      if (i + (1 << j) >= n - 1) break;
      int nx = i + (1 << (j - 1));
      for (int k1 = 0; k1 <= 1; k1++) {
        for (int k2 = 0; k2 <= 1; k2++) {
          for (int k3 = 0; k3 <= 1; k3++) {
            for (int k4 = 0; k4 <= 1; k4++) {
              dp[i][j][k1][k2] = min(dp[i][j][k1][k2],
                dp[i][j - 1][k1][k3] + dp[nx][j - 1][k4][k2]
                + dist[nx][k3][k4]);
            }
          }
        }
      }
    }
  }

  int m;
  cin >> m;
  while (m--) {
    array<int, 2> x, y;
    cin >> x >> y;
    x[0]--; x[1]--; y[0]--; y[1]--;
    int lyx = max(x[0], x[1]);
    int lyy = max(y[0], y[1]);
    if (lyx > lyy) {
      swap(lyx, lyy);
      swap(x, y);
    }
    if (lyy == lyx) {
      cout << getNormalDist(x, y) << "\n";
      continue;
    }

    int r = lyy - 1;
    int64_t d = getNormalDist(door[r][0], door[r][1]);
    array<array<int64_t, 2>, 2> cur, tmp;

    cur[0] = { 0LL, d }; cur[1] = { d, 0LL };

    while (r != lyx) {
      int j = int(log(r - lyx) / log(2));
      int i = r - (1 << j);
      for (int k1 = 0; k1 <= 1; k1++) {
        for (int k2 = 0; k2 <= 1; k2++) {
          tmp[k1][k2] = 0x3f3f3f3f3f3f3f3f;
          for (int k3 = 0; k3 <= 1; k3++) {
            for (int k4 = 0; k4 <= 1; k4++) {
              tmp[k1][k2] = min(tmp[k1][k2],
                dp[i][j][k1][k3] + cur[k4][k2]
                + dist[r][k3][k4]
              );
            }
          }
        }
      }
      swap(cur, tmp);
      r = i;
    }

    int64_t ans = 0x3f3f3f3f3f3f3f3f;
    for (int k1 = 0; k1 <= 1; k1++) {
      int d1 = getNormalDist(x, door[lyx][k1]);
      for (int k2 = 0; k2 <= 1; k2++) {
        int d2 = getdist(y, door[lyy - 1][k2], k2);
        ans = min(ans, d1 + d2 + cur[k1][k2]);
      }
    }

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