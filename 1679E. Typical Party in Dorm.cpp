#include<bits/stdc++.h>
using namespace std;
const int P = 998244353;
template<class T>
T qpow(T n, int k) {
  T res = 1;
  for (; k; k >>= 1, n *= n) {
    if (k & 1) {
      res *= n;
    }
  }
  return res;
}
template<int P = P>
struct ModInt {
  int x;
  ModInt(int x = 0) : x(mod(x)) {}
  int val() const {
    return x;
  }
  // assume -P <= x < 2P
  int mod(int x) {
    if (x < 0) {
      x += P;
    }
    if (x >= P) {
      x -= P;
    }
    return x;
  }
  void print(char seperator = ' ') {
    printf("%d%c", x, seperator);
  }
  void println() {
    printf("%d\n", x);
  }
  ModInt operator-() const {
    return ModInt(P - x);
  }
  ModInt<P> inv() const {
    assert(x != 0);
    return qpow(*this, P - 2);
  }
  ModInt<P>& operator*=(const ModInt& rhs) {
    x = int64_t(x) * rhs.x % P;
    return *this;
  }
  ModInt& operator+=(const ModInt& rhs) {
    x = mod(x + rhs.x);
    return *this;
  }
  ModInt& operator-=(const ModInt& rhs) {
    x = mod(x - rhs.x);
    return *this;
  }
  ModInt& operator/=(const ModInt& rhs) {
    return *this *= rhs.inv();
  }
  friend ModInt operator*(const ModInt& lhs, const ModInt& rhs) {
    ModInt res = lhs;
    res *= rhs;
    return res;
  }
  friend ModInt operator+(const ModInt& lhs, const ModInt& rhs) {
    ModInt res = lhs;
    res += rhs;
    return res;
  }
  friend ModInt operator-(const ModInt& lhs, const ModInt& rhs) {
    ModInt res = lhs;
    res -= rhs;
    return res;
  }
  friend ModInt operator/(const ModInt& lhs, const ModInt& rhs) {
    ModInt res = lhs;
    res /= rhs;
    return res;
  }
};
const int S = 18;
const int N = 1003;
int d[N][N], p[N][N];
ModInt<P> dp[1 << S][S];
void solve() {
  int n, q;
  string s;
  cin >> n >> s >> q;
  memset(dp, 0, sizeof(dp));
  memset(d, 0, sizeof(d));
  int num = count(s.begin(), s.end(), '?');
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) p[i][j] = num;
  for (int len = 1; len <= n; len++) {
    for (int i = 0; i + len <= n; i++) {
      int j = i + len - 1;

      int& curd = d[i][j],
        & curp = p[i][j];

      if (i == j) {
        curp = num;
      }
      else {
        int cnt = (s[i] == '?') + (s[j] == '?');

        if (s[i] != s[j] && cnt == 0) {
          curp = -1;
          continue;
        }
        curd = d[i + 1][j - 1];
        curp = p[i + 1][j - 1] - 1;

        if (cnt == 0) curp++;
        if (curp < 0) continue;

        if (cnt == 1) {
          char ch = s[i] == '?' ? s[j] : s[i];
          curd |= (1 << (ch - 'a'));
        }
      }

      if (curp < 0) continue;
      for (int k = 1; k < S; k++) {
        dp[curd][k] += qpow(ModInt<P>(k), curp);
      }
    }
  }

  for (int i = 0; i < S; i++) {
    for (int j = 0; j < (1 << S); j++) {
      if ((1 << i) & j) {
        for (int k = 1; k < S; k++)
          dp[j][k] += dp[(1 << i) ^ j][k];
      }
    }
  }
  while (q--) {
    cin >> s;
    int t = 0;
    for (auto it : s) t |= (1 << (it - 'a'));
    cout << dp[t][s.length()].val() << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }

}