#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int S = 10, N = 50002, MOD = 998244353;
int camp[1 << S];
int conn[S][S];
int dp[2][1 << S];
int trans[1 << S][S];
void solve(int case_t) {
  int n, m;
  cin >> n >> m;
  memset(conn, 0, sizeof(conn));
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    conn[u][v] = conn[v][u] = 1;
  }
  //计算camp 

  memset(camp, -1, sizeof(camp));
  for (int mask = 0; mask < (1 << S); mask++) {
    for (int j = 0; j < S; j++) {
      if (!(mask & (1 << j))) continue;
      for (int k = j + 1; k < S; k++) {
        if (conn[j][k] && (camp[mask] & (1 << k))) {
          camp[mask] ^= 1 << k;
        }
      }
    }
  }

  // 计算trans
  memset(trans, 0, sizeof(trans));
  for (int mask = 0; mask < (1 << S); mask++) {
    for (int c = 0; c < S; c++) {
      trans[mask][c] = 1 << c;
      for (int j = 0; j < S; j++) {
        if ((mask & (1 << j)) && conn[c][j]) {
          trans[mask][c] |= 1 << j;
        }
      }
    }
  }
  // dp
  memset(dp, 0, sizeof(dp));
  int cur = 0;
  dp[0][0] = 1;
  // O(n * S * 2^S)
  for (int i = 0; i < n; i++) {
    memset(dp[cur ^ 1], 0, sizeof(dp[0]));
    for (int mask = 0; mask < (1 << S); mask++) {
      if (dp[cur][mask] == 0) continue;
      for (int c = 0; c < S; c++) {
        if (camp[mask] & (1 << c)) {
          dp[cur ^ 1][trans[mask][c]] = (dp[cur ^ 1][trans[mask][c]] + dp[cur][mask]) % MOD;
        }
      }
    }
    cur ^= 1;
  }

  int ans = 0;
  for (int mask = 1; mask < (1 << S); mask++) {
    ans = (ans + dp[cur][mask]) % MOD;
  }


  printf("%d\n", ans);
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  int t = 1;
  //cin >> t;
  while (t--) {
    solve(t);
  }
}