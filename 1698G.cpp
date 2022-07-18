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
int n;
string s;
// mod就是s对应的多项式P(x)
int64_t mod;

/**
 * @brief i * j % mod，这个乘法是GF(2)上的多项式乘法
 *    就是把二进制乘法中的加法替换成GF(2)的加法即异或
 *
 * @param i
 * @param j
 * @return int64_t
 */
int64_t mul(int64_t i, int64_t j) {
  int64_t res = 0;
  for (int k = 0; k < n - 1; k++) {
    if (i & (1LL << k)) res ^= j;
    j <<= 1;
    if (j & (1LL << (n - 1))) j ^= mod;
  }
  return res;
}

/**
 * @brief 2^i % mod。对应x^i
 *
 * @param i
 * @return int64_t
 */
int64_t pow(int64_t i) {
  int64_t res = 1;
  int64_t b = 2;
  while (i) {
    if (i & 1) res = mul(res, b);
    b = mul(b, b);
    i >>= 1;
  }
  return res;
}

void solve() {
  cin >> s;
  vector<int> pos;
  for (int i = 0; i < s.length();i++) {
    if (s[i] == '1') {
      pos.push_back(i);
    }
  }
  // 特判掉1的个数小于等于2的情况
  if (pos.size() == 0) {
    cout << "-1\n";
    return;
  }
  else if (pos.size() == 1) {
    cout << pos[0] + 1 << " " << pos[0] + 2 << "\n";
    return;
  }
  else if (pos.size() == 2) {
    cout << pos[0] + 1 << " " << pos[1] + 1 << "\n";
    return;
  }

  int offset = pos[0];
  // mod就是s对应的多项式的二进制表示
  mod = 0;
  for (int p : pos) {
    mod |= (1LL << (p - offset));
  }

  n = pos.back() - offset + 1;
  int h = (n + 1) / 2;
  int64_t val = mod;
  int64_t prod = 1;

  // 对mod进行分解，分解成不可约多项式

  // 枚举可能的因子，多项式k(x)
  for (int64_t k = 3; k < (1LL << h); k++) if (k & 1) {
    int64_t num = 0;
    while (true) {
      int64_t curr = val;
      int64_t other = 0;
      // 判断curr能不能被k整除（多项式整除）
      for (int bit = 0; bit < n; bit++) if (curr & (1LL << bit)) {
        curr ^= k << bit;
        other ^= 1LL << bit;
      }

      if (curr == 0) {
        val = other;
        num++;
      }
      else
        break;
    }

    // mod 有因子k的num次方
    if (num) {
      int64_t d = 1LL << (63 - __builtin_clzll(k));
      prod *= d - 1;
      for (int y = 1; y < num; y++)
        prod *= d;
    }
  }

  if (val > 1) prod *= (1LL << (63 - __builtin_clzll(val))) - 1;

  int64_t ans = 1LL << 60;
  for (int64_t x = 1; x * x <= prod; x++) {
    if (prod % x == 0) {
      if (pow(x) == 1) ans = min(ans, x);
      if (pow(prod / x) == 1) ans = min(ans, prod / x);
    }
  }
  cout << 1 + offset << ' ' << ans + 1 + offset << endl;

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