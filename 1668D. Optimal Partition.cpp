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
int a[N];
int64_t sum[N];
void solve(int case_t) {
  int n;
  read_int(n);
  sum[0] = 0;
  repeat(i, 1, n) {
    read_int(a[i]);
    sum[i] = sum[i - 1] + a[i];
    a[i] = ((a[i] < 0) ? -1 : (a[i] > 0));
  }

  map<int64_t, int64_t> mp;
  int64_t dp = mp[0] = 0;

  repeat(i, 1, n) {
    dp += a[i];

    if (mp.begin()->first < sum[i]) {
      auto iter = mp.lower_bound(sum[i]);
      --iter;
      dp = max(dp, i + iter->second);
    }

    if (mp.count(sum[i]))
      mp[sum[i]] = max(mp[sum[i]], dp - i);
    else
      mp[sum[i]] = dp - i;

    auto iter = mp.find(sum[i]);
    while (true) {
      auto iter2 = iter;
      if (++iter2 == mp.end()) break;
      if (iter2->second <= iter->second) mp.erase(iter2);
      else break;
    }
  }
  printf("%lld\n", dp);

}



int main() {
  int t = 1;
  read_int(t);
  repeat(i, 1, t) {
    solve(i);
  }
  return 0;
}