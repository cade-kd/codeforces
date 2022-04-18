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
const int N = 500005;
char s[3][N];
int pa[N * 3];
int findpa(int x) {
  return pa[x] ? pa[x] = findpa(pa[x]) : x;
}
bool unite(int a, int b) {
  a = findpa(a);
  b = findpa(b);
  if (a == b) return false;
  pa[b] = a;
  return true;
}

void solve(int case_t) {
  int n;
  read_int(n);
  bzeron(pa, n + 1);
  vector<int> freeCnt(n + 1);
  repeat(i, 0, 2) {
    gets(s[i] + 1);
    repeat(j, 1, n) {
      freeCnt[j] += s[i][j] - '0';
    }
  }
  repeat(i, 1, n) freeCnt[i] += freeCnt[i - 1];

  vector<int> vEdgeCnt(n + 1), hEdgeCnt(n + 1);
  s[0][0] = s[1][0] = s[2][0] = 0;
  repeat(i, 1, n) {
    repeat(j, 0, 1) {
      if (s[j][i] == '1' && s[j + 1][i] == '1'
        && unite(j * n + i, (j + 1) * n + i))
        vEdgeCnt[i]++;
    }
    repeat(j, 0, 2) {
      if (s[j][i] == '1' && s[j][i - 1] == '1'
        && unite(j * n + i, j * n + i - 1))
        hEdgeCnt[i]++;
    }
  }
  repeat(i, 1, n) {
    vEdgeCnt[i] += vEdgeCnt[i - 1];
    hEdgeCnt[i] += hEdgeCnt[i - 1];
  }

  vector<int> nextNon101(n + 1, n + 1);

  downrep(i, n, 1) {
    if (s[0][i] == '1' && s[1][i] == '0' && s[2][i] == '1') {
      nextNon101[i] = nextNon101[i + 1];
    }
    else {
      nextNon101[i] = i;
    }
  }

  vector<int> prevNon101(n + 1, 0);
  repeat(i, 1, n) {
    if (s[0][i] == '1' && s[1][i] == '0' && s[2][i] == '1') {
      prevNon101[i] = prevNon101[i - 1];
    }
    else {
      prevNon101[i] = i;
    }
  }

  int q;
  read_int(q);
  while (q--) {
    int l, r;
    read_ints(l, r);
    if (nextNon101[l] > r) {
      puts("2");
      continue;
    }
    int free = freeCnt[r] - freeCnt[l - 1];
    int edge = vEdgeCnt[r] - vEdgeCnt[l - 1]
      + hEdgeCnt[r] - hEdgeCnt[l];
    int ans = free - edge;

    function<bool(int)> is111 = [&](int i) -> bool {
      return s[0][i] == '1' && s[1][i] == '1' && s[2][i] == '1';
    };

    if (prevNon101[l] && is111(prevNon101[l])
      && nextNon101[l] != l && is111(nextNon101[l])) {
      --ans;
    }
    printf("%d\n", ans);
  }
}

int main() {
  int t = 1;
  // read_int(t);
  repeat(i, 1, t) {
    solve(i);
  }
  return 0;
}