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

template<int P>
istream& operator>>(istream& ins,
  ModInt<P> m) {
  ins >> m.x;
  return ins;
}

template<int P>
ostream& operator<<(ostream& outs,
  ModInt<P> m) {
  outs << m.x;
  return outs;
}

const int N = 4e5 + 5;

vector<ModInt<P>> fac(N), invfac(N);

bool inited = false;
void initFac(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i;
  invfac[n] = fac[n].inv();
  for (int i = n; i >= 1; i--) invfac[i - 1] = invfac[i] * i;
}

ModInt<> binom(int n, int m) {
  if (!inited) {
    initFac(N - 1);
    inited = true;
  }
  return fac[n] * invfac[m] * invfac[n - m];
};
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 1);
  cin >> a;
  ModInt<P> ans = 0;
  for (int i = 0; i <= n; i++) {
    if (a[i] == 0) break;
    ans += binom(i + a[i], a[i] - 1);
  }
  cout << ans << "\n";
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