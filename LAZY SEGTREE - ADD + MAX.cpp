struct ST {
  int n;
  vector<int> t, lazy;
 
  ST(int N) : n(N) {
    int dim = 1;
    while (dim < n) {
      dim *= 2;
    }
    t.resize(dim * 2);
    lazy.resize(dim * 2);
  }
 
  void updateNode(int x, int len, int v) {
    t[x] += v;
    lazy[x] += v;
  }
 
  void push(int x, int lx, int rx) {
    if (lazy[x] == 0) {
      return;
    }
    int mid = (lx + rx) / 2;
    int len[] = {mid - lx + 1, rx - mid};
    updateNode(x * 2, len[i], lazy[x]);
    updateNode(x * 2 + 1, len[i], lazy[x]);
    lazy[x] = 0;
  }
 
  void update(int x, int lx, int rx, int st, int dr, int v) {
    if (dr < st) {
      return;
    }
    if (st <= lx && rx <= dr) {
      updateNode(x, rx - lx + 1, v);
      return;
    }
    push(x, lx, rx);
    int mid = (lx + rx) / 2;
    if (st <= mid) {
      update(x * 2, lx, mid, st, dr, v);
    }
    if (mid < dr) {
      update(x * 2 + 1, mid + 1, rx, st, dr, v);
    }
    t[x] = max(t[x * 2], t[x * 2 + 1]);
  }
 
  void update(int st, int dr, int v) {
    update(1, 1, n, st, dr, v);
  }
 
  int query(int x, int lx, int rx, int st, int dr) {
    if (st <= lx && rx <= dr) {
      return t[x];
    }
    push(x, lx, rx);
    int mid = (lx + rx) / 2, ans = -INF;
    if (st <= mid) {
      maxSelf(ans, query(x * 2, lx, mid, st, dr));
    }
    if (mid < dr) {
      maxSelf(ans, query(x * 2 + 1, mid + 1, rx, st, dr));
    }
    return ans;
  }
 
  int query(int st, int dr) {
    return query(1, 1, n, st, dr);
  }
};