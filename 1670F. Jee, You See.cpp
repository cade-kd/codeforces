#include<bits/stdc++.h>
using namespace std;
const int P = 1e9 + 7;
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
const int N = 1002, B = 61;
ModInt<P> dp[B + 1][2 * N], fac[N], invfac[N];
int done[B + 1][2 * N];
void init_fac(int n) {
  fac[0] = 1;
  for (int i = 1; i < n; i++) fac[i] = fac[i - 1] * i;
  invfac[n - 1] = fac[n - 1].inv();
  for (int i = n - 1; i > 0; i--) invfac[i - 1] = invfac[i] * i;
}

ModInt<> binom(int n, int m) {
  return fac[n] * invfac[m] * invfac[n - m];
};

int n;
int64_t z;
ModInt<P> dfs(int i, int m, const int64_t limit) {
  if (m < 0) return 0;
  if (i == -1) return 1;
  ModInt<P>& ans = dp[i][m];
  if (done[i][m]) return ans;
  ans = 0;
  done[i][m] = 1;
  for (int j = z >> i & 1; j <= n; j += 2) {
    int nextm = min(2 * n, (int(limit >> i & 1) + m - j) << 1);
    ans += binom(n, j) * dfs(i - 1, nextm, limit);
  }
  return ans;
}

ModInt<P> cal(const int64_t limit) {
  memset(done, 0, sizeof(done));
  return dfs(B, 0, limit);

}
int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0); cout.tie(0);

  init_fac(N);
  int64_t l, r;
  cin >> n >> l >> r >> z;
  cout << (cal(r) - cal(l - 1)).val() << endl;

}