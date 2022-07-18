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

/**
 * 这个板子，相当的慢。有空再看看怎么改。
 * @brief 带Lazy操作的线段树。
 *     其实下面用参数传入的函数，也可以通过运算符重载去做
 * @tparam T  节点保存的数据类型
 * @tparam T(*t_op)(T&&, T&&) 区间信息结合函数，t_开头的函数表示泛型参数函数
 * @tparam T(*t_e)() 返回节点初始化状态的函数
 * @tparam T2 区间坐标的类型，只能是int或者int64
 * @tparam F lazy信息的类型
 * @tparam T(*t_mapping)(T&, F&, T2, T2) 由节点信息和lazy信息计算出当前的节点信息
 * @tparam F(*t_composition)(F, F) lazy信息结合函数
 * @tparam F(*t_e1)() 返回lazy信息初始化状态的函数
 */
template <
  typename T, T(*t_op)(T&&, T&&), T(*t_e)(),
  typename T2,
  typename F, T(*t_mapping)(T&, F&, T2, T2),
  F(*t_composition)(F&, F&), F(*t_e1)()
>
class AbstractLazySegtree {
protected:
  // 静态断言，确保T2类型是int或者int64_t
  static_assert(std::is_same<int, T2>::value
    || std::is_same<int64_t, T2>::value,
    "Type T2 must be int or int64_t");

  // 区间范围1 ~ n, 
  T2 n;
  //root为根节点
  int root;
  // 节点保存的信息
  vector< T > v;
  // lazy 信息
  vector< F > lazy;
  // m_开头的表示内部函数（private或者protected）
  virtual inline int m_lson(int o) = 0;
  virtual inline int m_rson(int o) = 0;

  inline void m_maintain(int o, int l, int r) {
    v[o] = t_op(std::forward<T>(v[l]), std::forward<T>(v[r]));
  }

  inline void m_pushdown(int o, T2 l, T2 r) {
    v[o] = t_mapping(v[o], lazy[o], l, r);
    if (l != r) {
      int ls = m_lson(o), rs = m_rson(o);
      lazy[ls] = t_composition(lazy[ls], lazy[o]);
      lazy[rs] = t_composition(lazy[rs], lazy[o]);
    }
    lazy[o] = t_e1();
  }

  void m_modify(F& x, T2 ql, T2 qr, T2 l, T2 r, int o) {
    m_pushdown(o, l, r);
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
      lazy[o] = x;
      m_pushdown(o, l, r);
      return;
    }
    T2 mid = (r - l) / 2 + l;
    int lson = m_lson(o), rson = m_rson(o);
    m_modify(x, ql, qr, l, mid, lson);
    m_modify(x, ql, qr, mid + 1, r, rson);
    m_maintain(o, lson, rson);
  }

  T m_query(T2 ql, T2 qr, T2 l, T2 r, int o) {
    m_pushdown(o, l, r);
    if (l > qr || r < ql) return t_e();
    if (l >= ql && r <= qr) return v[o];

    T2 mid = (r - l) / 2 + l;

    return t_op(m_query(ql, qr, l, mid, m_lson(o)),
      m_query(ql, qr, mid + 1, r, m_rson(o)));
  }

public:
  AbstractLazySegtree(int n) :n(n), root(1) {  }

  void modify(F& x, T2 l, T2 r) { m_modify(x, l, r, 1, n, root); }
  T query(T2 l, T2 r) { return m_query(l, r, 1, n, root); }
};

template <
  typename T, T(*t_op)(T&&, T&&), T(*t_e)(),
  typename T2,
  typename F, T(*t_mapping)(T&, F&, T2, T2),
  F(*t_composition)(F&, F&), F(*t_e1)(),
  bool PreAlloc = true>
class LazySegtree
  : public AbstractLazySegtree <
  T, t_op, t_e, T2, F, t_mapping, t_composition, t_e1> {


  using Base = AbstractLazySegtree<T, t_op, t_e, T2, F, t_mapping, t_composition, t_e1>;
  inline int m_lson(int o) { return o << 1; }
  inline int m_rson(int o) { return o << 1 | 1; }

public:
  LazySegtree(int n)
    :AbstractLazySegtree<T, t_op, t_e, T2, F, t_mapping, t_composition, t_e1>(n) {
    Base::v.resize(n << 2);
    Base::lazy.resize(n << 2);
  }
};

/**
 * @brief 偏特化
 * PreAlloc = false
 */
template <
  typename T, T(*t_op)(T&&, T&&), T(*t_e)(),
  typename T2,
  typename F, T(*t_mapping)(T&, F&, T2, T2),
  F(*t_composition)(F&, F&), F(*t_e1)()
>
class LazySegtree<
  T, t_op, t_e, T2, F, t_mapping, t_composition, t_e1, false>
  : public AbstractLazySegtree <
  T, t_op, t_e, T2, F, t_mapping, t_composition, t_e1> {

  using Base = AbstractLazySegtree<T, t_op, t_e, T2, F, t_mapping, t_composition, t_e1>;

  vector<int> lc, rc;

  inline int m_getNo() {
    Base::v.emplace_back(t_e());
    Base::lazy.emplace_back(t_e1());
    lc.push_back(0);
    rc.push_back(0);
    return rc.size() - 1;
  }

  inline int m_lson(int o) {
    if (!lc[o]) lc[o] = m_getNo();
    return lc[o];
  }

  inline int m_rson(int o) {
    if (!rc[o]) rc[o] = m_getNo();
    return rc[o];
  }

public:
  // 0号不用，1号作为根
  LazySegtree(int n) :Base(n), lc(2), rc(2) {
    Base::v.resize(2);
    Base::lazy.resize(2);
  }
};
#ifndef ONLINE_JUDGE
const int N = 100;
#else
const int N = 200005;
#endif
int vis[N] = { 0 };
struct Node {
  int val;
  int64_t x, bias, y;
  Node() :val(0), x(0), y(0), bias(1) {  }
  inline void cpy(Node& node) {
    memcpy(this, &node, sizeof(Node));
  }
  Node(Node& node) {
    cpy(node);
  }
  Node(Node&& node) :Node(node) {}
  Node& operator=(Node& node) {
    cpy(node);
    return *this;
  }
  Node& operator=(Node&& node) noexcept {
    cpy(node);
    return *this;
  }

};

struct LazyNode {
  using Mat = array<array<int64_t, 3>, 3>;
  Mat mat;
  int type;

  LazyNode(bool identity = true) :type(0) {
    for (int i = 0;i < 3;i++) fill(mat[i].begin(), mat[i].end(), 0);
    if (identity)
      mat[0][0] = mat[1][1] = mat[2][2] = 1;
  }
  LazyNode(LazyNode& node) {
    type = node.type;
    mat = node.mat;
  }
  LazyNode(LazyNode&& node) noexcept {
    mat.swap(node.mat);
    type = node.type;
  }
  LazyNode(Mat& a) :mat(a), type(0) {}
  LazyNode& operator=(LazyNode& that) {
    mat = that.mat;
    type = that.type;
    return *this;
  }
  // 赋值需要移动构造函数
  LazyNode& operator=(LazyNode&& that) {
    mat.swap(that.mat);
    type = that.type;
    return *this;
  }
};

// 这些不能是局部变量，不然会链接错误
using T = Node;
T op(T&& a, T&& b) {
  T c = a;

  if (!a.val) {
    memset(&c, 0, sizeof(T));
  }

  if (b.val) {
    c.val = 1;
    c.x += b.x;
    c.y += b.y;
    c.bias += b.bias;
  }
  return c;
};
using T2 = int;
using F = LazyNode;
T mapping(T& cur, F& laz, T2 l, T2 r) {
  T node = std::move(cur);
  if (laz.type == 1) {
    node.val ^= 1;
    return node;
  }
  // T node;
  // node.val = cur.val;
  node.y = laz.mat[0][0] * node.y
    + laz.mat[0][1] * node.x + laz.mat[0][2] * node.bias;
  node.x = laz.mat[1][1] * node.x + laz.mat[1][2] * node.bias;
  node.bias = laz.mat[2][2] * node.bias;
  return node;
};

F composition(F& a, F& b) {
  // assert(a.type == 0 && a.type == 0);
  LazyNode node(false);
  for (int i = 0; i < 3; i++) {
    for (int k = 0; k < 3; k++) {
      for (int j = i; j < 3; j++) {
        node.mat[i][j] += a.mat[i][k] * b.mat[k][j];
      }
    }
  }
  return node;
};
T e() { return T(); };
F e1() { return F(); };

LazySegtree < T, op, e, T2, F,
  mapping, composition, e1, false> segtree(N);
void solve() {

  int q, d;
  cin >> q >> d;

  array<array<int64_t, 3>, 3> a = { { {1, 1, 0},{0, 1, 1},{0, 0, 1} } },
    ainv = { { {1, -1, 1},{0, 1, -1}, {0, 0, 1} } };

  F mat(a), minv(ainv);

  while (q--) {
    int i;
    cin >> i;
    mat.type = 1;
    segtree.modify(mat, i, i);
    mat.type = 0;
    if (vis[i] ^= 1) {
      if (i > 1) segtree.modify(mat, max(1, i - d), i - 1);
    }
    else {
      if (i > 1) segtree.modify(minv, max(1, i - d), i - 1);
    }

    cout << segtree.query(1, N).y << "\n";
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