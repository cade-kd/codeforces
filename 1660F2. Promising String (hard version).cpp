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

template<class T = int>
class BIT {
    int n, sum;
    vector<T> c;
public:
    BIT() :n(-1) {}
    BIT(int n) :n(n), c(n + 1), sum(0) {}

    void reset(int n) {
        this->n = n;
        c.assign(n + 1, 0);
        sum = 0;
    }

    // int lowbit(int x) {
    //   return x & (-x);
    // }

    void add(int i, T k) {
        if (i <= n)
            sum = sum + k;
        while (i <= n) {
            c[i] = c[i] + k;
            i += lowbit(i);
        }
    }
    void add_int(int l, int r, T k) {
        assert(l <= r);
        add(l, k);
        add(r + 1, -k);
    }

    T pre_sum(int i) {
        T res = 0;
        while (i > 0) {
            res = res + c[i];
            i -= lowbit(i);
        }
        return res;
    }

    T suf_sum(int i) {
        return sum - pre_sum(i - 1);
    }
    //区间[a,b]的和
    T int_sum(int a, int b) {
        return pre_sum(b) - pre_sum(a - 1);
    }
};
BIT<> bit[3];
char s[200004];
void solve(int case_t) {
    int n;
    read_int(n);
    gets(s + 1);
    repeat(i, 0, 2)  bit[i].reset(2 * n + 2);

    int diff = 0;
    long long ans = 0;
    bit[0].add(n + 1, 1);
    repeat(i, 1, n) {
        diff += s[i] == '-' ? 1 : -1;
        int cur = (diff % 3 + 3) % 3;
        int pos = diff + n + 1;
        ans += bit[cur].pre_sum(pos);
        bit[cur].add(pos, 1);
    }
    printf("%lld\n", ans);
}

int main() {
    int t = 1;
    read_int(t);
    repeat(i, 1, t) {
        solve(i);
    }
    return 0;
}