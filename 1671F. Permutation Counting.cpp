#include<bits/stdc++.h>
using namespace std;
#define lson (i<<1)
#define rson (i<<1|1)
#define repeat(i, s, n) for(int i = s; i <= n; ++i)
#define foreach(i,items) for(auto &i: items)
#define downrep(i, n, s) for(int i = n; i >= s; --i)
#define lowbit(x) (x&-x)
#define bzero(x) memset(x, 0, sizeof(x))
#define bzeron(x, n) memset(x, 0, (n) * sizeof *x)
#define gcd(a,b) __gcd(a,b)
#define brkline puts("")
#define spaceout putchar(' ')
#define all(a) a.begin(),a.end()
#define pb	push_back

// using i128=__int128; //这个是非标准，不一定支持
using i64 = long long;
using i32 = int;
const int INF = 0x3f3f3f3f;
const double tol = 1e-8;
const int P = 998244353;

int pop_count(i64 x) {
  return __builtin_popcountll(x);
}
int pop_count(int x) {
  return __builtin_popcount(x);
}

template<typename S, typename T>
bool check_and_save_min_in_lhs(S& lhs, const T& rhs) {
  return lhs < rhs ? 1 : lhs = rhs, 0;
}

template<typename S, typename T>
bool check_and_save_max_in_lhs(S& lhs, const T& rhs) {
  return lhs > rhs ? 1 : lhs = rhs, 0;
}
template<typename T>
T min_all(T ele) {
  return ele;
}

template<typename T, typename ...Args>
T min_all(T fst_el, Args ...others) {
  return min_all(fst_el, mins(others...));
}

template<typename T>
T maxs(T ele) {
  return ele;
}

template<typename T, typename ...Args>
T maxs(T fst_el, Args ...others) {
  return max(fst_el, maxs(others...));
}

template<typename T>
void read_int(T& num) {
  bool positive = true;
  char ch; num = 0;
  while (isspace(ch = getchar()));
  if (ch == '-')	positive = false;
  else num = ch - '0';
  while ((ch = getchar()) >= '0' && ch <= '9')
    num = num * 10 + ch - '0';
  if (!positive) num = -num;
}

void read_ints() {};
template <typename T, typename ...Args>
void read_ints(T& fst_el, Args&... others) { read_int(fst_el);read_ints(others...); }

template<typename T>
void int_out(T num) {
  if (num < 0) {
    putchar('-');
    num = -num;
  }
  if (num > 9)
    int_out(num / 10);
  putchar(num % 10 + '0');
}

void int_outs() { brkline; }
template<typename T, typename ...Args>
void int_outs(T fst_ele, Args ...others) {
  int_out(fst_ele);
  spaceout;
  int_outs(others...);
}


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
    else if (x >= P) {
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
    x = i64(x) * rhs.x % P;
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

const int K = 13;
ModInt<> c[K][K][K], f[1 << (K - 1)][K << 1][K][K], dp[K][K << 1][K][K];

void init() {
  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < K; ++j) {
      for (int k = 0; k < K; ++k) {
        c[i][j][k] = 0;
      }
    }
  }
  for (int i = 0; i < (1 << (K - 1)); ++i) {
    for (int j = 0; j < 2 * K; ++j) {
      for (int k = 0; k < K; ++k) {
        for (int t = 0; t < K; ++t) {
          f[i][j][k][t] = 0;
        }
      }
    }
  }

  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < 2 * K; ++j) {
      for (int k = 0; k < K; ++k) {
        for (int t = 0; t < K; ++t) {
          dp[i][j][k][t] = 0;
        }
      }
    }
  }

}

std::vector<ModInt<>> invfac(K + 1);

void init_fac(int n, int mod) {
  invfac[0] = 1;
  for (int i = 1; i <= n; ++i)
    invfac[i] = qpow(ModInt<>(i), mod - 2);
}

ModInt<> binom(int n, int k) {
  if (n < 0 || n < k || k < 0) return 0;
  ModInt<> res = 1;
  for (int i = n; i > n - k; i--)
    res *= i;
  for (int i = 1; i <= k; i++)
    res *= invfac[i];
  return res;
}

// void precalc() {
//   c[2][1][1] = 1;
//   c[3][1][2] = 2;
//   c[3][2][3] = 1;
//   c[4][1][3] = 3;
//   c[4][1][4] = 1;
//   c[4][2][3] = 1;
//   c[4][2][4] = 4;
//   c[4][2][5] = 3;
//   c[4][3][6] = 1;
//   c[5][1][4] = 4;
//   c[5][1][5] = 2;
//   c[5][1][6] = 2;
//   c[5][2][4] = 4;
//   c[5][2][5] = 12;
//   c[5][2][6] = 12;
//   c[5][2][7] = 9;
//   c[5][2][8] = 3;
//   c[5][3][5] = 2;
//   c[5][3][6] = 4;
//   c[5][3][7] = 6;
//   c[5][3][8] = 6;
//   c[5][3][9] = 4;
//   c[5][4][10] = 1;
//   c[6][1][5] = 5;
//   c[6][1][6] = 3;
//   c[6][1][7] = 4;
//   c[6][1][8] = 3;
//   c[6][1][9] = 1;
//   c[6][2][5] = 10;
//   c[6][2][6] = 28;
//   c[6][2][7] = 35;
//   c[6][2][8] = 35;
//   c[6][2][9] = 30;
//   c[6][2][10] = 17;
//   c[6][2][11] = 8;
//   c[6][3][5] = 1;
//   c[6][3][6] = 13;
//   c[6][3][7] = 29;
//   c[6][3][8] = 41;
//   c[6][3][9] = 44;
//   c[6][3][10] = 45;
//   c[6][3][11] = 30;
//   c[6][4][7] = 1;
//   c[6][4][8] = 4;
//   c[6][4][9] = 7;
//   c[6][4][10] = 7;
//   c[6][4][11] = 11;
//   c[7][1][6] = 6;
//   c[7][1][7] = 4;
//   c[7][1][8] = 6;
//   c[7][1][9] = 6;
//   c[7][1][10] = 6;
//   c[7][1][11] = 2;
//   c[7][2][6] = 20;
//   c[7][2][7] = 55;
//   c[7][2][8] = 80;
//   c[7][2][9] = 95;
//   c[7][2][10] = 101;
//   c[7][2][11] = 94;
//   c[7][3][6] = 6;
//   c[7][3][7] = 50;
//   c[7][3][8] = 118;
//   c[7][3][9] = 186;
//   c[7][3][10] = 230;
//   c[7][3][11] = 260;
//   c[7][4][7] = 3;
//   c[7][4][8] = 18;
//   c[7][4][9] = 48;
//   c[7][4][10] = 85;
//   c[7][4][11] = 113;
//   c[7][5][10] = 2;
//   c[7][5][11] = 4;
//   c[8][1][7] = 7;
//   c[8][1][8] = 5;
//   c[8][1][9] = 8;
//   c[8][1][10] = 9;
//   c[8][1][11] = 11;
//   c[8][2][7] = 35;
//   c[8][2][8] = 96;
//   c[8][2][9] = 155;
//   c[8][2][10] = 207;
//   c[8][2][11] = 250;
//   c[8][3][7] = 21;
//   c[8][3][8] = 145;
//   c[8][3][9] = 358;
//   c[8][3][10] = 616;
//   c[8][3][11] = 859;
//   c[8][4][7] = 1;
//   c[8][4][8] = 26;
//   c[8][4][9] = 124;
//   c[8][4][10] = 313;
//   c[8][4][11] = 567;
//   c[8][5][9] = 3;
//   c[8][5][10] = 16;
//   c[8][5][11] = 53;
//   c[9][1][8] = 8;
//   c[9][1][9] = 6;
//   c[9][1][10] = 10;
//   c[9][1][11] = 12;
//   c[9][2][8] = 56;
//   c[9][2][9] = 154;
//   c[9][2][10] = 268;
//   c[9][2][11] = 389;
//   c[9][3][8] = 56;
//   c[9][3][9] = 350;
//   c[9][3][10] = 898;
//   c[9][3][11] = 1654;
//   c[9][4][8] = 8;
//   c[9][4][9] = 126;
//   c[9][4][10] = 552;
//   c[9][4][11] = 1404;
//   c[9][5][9] = 4;
//   c[9][5][10] = 48;
//   c[9][5][11] = 204;
//   c[9][6][11] = 1;
//   c[10][1][9] = 9;
//   c[10][1][10] = 7;
//   c[10][1][11] = 12;
//   c[10][2][9] = 84;
//   c[10][2][10] = 232;
//   c[10][2][11] = 427;
//   c[10][3][9] = 126;
//   c[10][3][10] = 742;
//   c[10][3][11] = 1967;
//   c[10][4][9] = 36;
//   c[10][4][10] = 448;
//   c[10][4][11] = 1887;
//   c[10][5][9] = 1;
//   c[10][5][10] = 43;
//   c[10][5][11] = 357;
//   c[10][6][11] = 6;
//   c[11][1][10] = 10;
//   c[11][1][11] = 8;
//   c[11][2][10] = 120;
//   c[11][2][11] = 333;
//   c[11][3][10] = 252;
//   c[11][3][11] = 1428;
//   c[11][4][10] = 120;
//   c[11][4][11] = 1302;
//   c[11][5][10] = 10;
//   c[11][5][11] = 252;
//   c[11][6][11] = 5;
//   c[12][1][11] = 11;
//   c[12][2][11] = 165;
//   c[12][3][11] = 462;
//   c[12][4][11] = 330;
//   c[12][5][11] = 55;
//   c[12][6][11] = 1;
// }

void resetf(int g) {
  for (int i = 0; i < (1 << g); ++i)
    for (int j = 0;j < K; ++j)
      for (int k = 0;k < K; ++k)
        for (int t = 0;t <= g; ++t)
          f[i][j][k][t] = 0;
}

void precal() {
  init();
  // 计算c (通过f)
  for (int g = 2; g < K; ++g) {
    resetf(g);

    f[0][0][0][0] = 1;
    for (int S = 0;S < (1 << g); ++S) {
      int bc = __builtin_popcount(S) + 1;
      for (int c1 = 0;c1 < K; ++c1)
        for (int c2 = 0;c2 < K; ++c2)
          for (int lst = 0;lst <= g; ++lst) {
            if (!f[S][c1][c2][lst].val()) continue;

            // 找到S中最大的数
            int mx = 0;
            for (int i = 1;i <= g; ++i)
              if ((S >> (i - 1)) & 1)
                mx = i;
            // 枚举下一个加入的
            for (int p = 1;p <= g; ++p)
              if (!((S >> (p - 1)) & 1)) {
                // 下一个加入的，满足mx[i] > i或为最后一个
                if (max(mx, p) > bc || bc == g) {
                  //加上递减对增加的数目
                  int h = c1 + (lst > p);
                  // 加上逆序对增加的数目
                  int t = c2 + __builtin_popcount(S & ((1 << g) - (1 << p)));
                  if (h < K && t < K)
                    f[S | (1 << (p - 1))][h][t][p] += f[S][c1][c2][lst];
                }
              }
          }
    }
    for (int h = 1;h < K; ++h)
      for (int t = 1;t < K; ++t)
        for (int p = 1;p <= g; ++p) {
          c[g][h][t] += f[(1 << g) - 1][h][t][p];
        }
  }
  // 可以使用打表代替上面的计算
  // precalc();
  // 计算dp
  // 打表
  // for (int g = 1;g < K; ++g)
  //   for (int h = 1;h < K; ++h)
  //     for (int t = 1;t < K; ++t) {
  //       if (c[g][h][t].val())
  //         printf("c[%d][%d][%d]=%d\n", g, h, t, c[g][h][t].val());
  //     }

  dp[0][0][0][0] = 1;
  for (int i = 0; i < K; ++i)
    for (int j = 0; j < 2 * K; ++j)
      for (int a = 0; a < K - 2; ++a)
        for (int b = 0; b < K - 2; ++b) {
          if (dp[i][j][a][b].val() == 0) continue;
          for (int g = 2; g < K; ++g)
            for (int h = 1; h < K - 1; ++h)
              for (int t = 1; t < K - 1; ++t) {
                if (j + g >= 2 * K || a + h > K - 2 || b + t > K - 2) continue;
                dp[i + 1][j + g][a + h][b + t] += dp[i][j][a][b] * c[g][h][t];
              }
        }
}

void solve(int case_t) {
  int n, k, x;
  read_ints(n, k, x);
  if (k == 0 && x == 0) {
    puts("1");
    return;
  }
  ModInt<> ans = 0;
  for (int i = 1; i < K; ++i)
    for (int j = 1; j < 2 * K; ++j)
      if (dp[i][j][x][k].val() != 0) {
        ans += dp[i][j][x][k] * binom(n - j + i, i);
      }
  ans.println();
}

int main() {
  init_fac(K, P);
  precal();
  int t = 1;
  read_int(t);
  repeat(i, 1, t) {
    solve(i);
  }
  return 0;
}