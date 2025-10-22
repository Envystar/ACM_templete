#include <bits/stdc++.h>
using i64 = long long;
constexpr int MAXN = 2E5;

template<typename Info, typename Tag, typename T = i64>
struct SegmentTree {
#define ls (id->l)
#define rs (id->r)
    struct Node {
        Node* l = nullptr;
        Node* r = nullptr;
        Tag tag;
        Info info;
    };
    SegmentTree() = default;
    SegmentTree(T n) : L(0), R(n - 1) {}
    SegmentTree(T L, T R) : L(L), R(R) {}
    void apply(Node* &id, const Tag &dx, T len) {
        if(id == nullptr) id = new Node();
        id->info.apply(dx, len);
        id->tag.apply(dx);
    }
    void pushdown(Node* &id, T l, T r) {
        if(id->tag == Tag()) return;
        T mid = l + r >> 1;
        apply(ls, id->tag, mid - l + 1);
        apply(rs, id->tag, r - mid);
        id->tag = Tag();
    }
#define pushdown(id) pushdown(id, l, r)
    void pushup(Node* id) {
        id->info = (ls == nullptr ? Info::unit() : ls->info) 
                 + (rs == nullptr ? Info::unit() : rs->info);
    }
    void update(T pos, const Tag &dx) {
        rangeUpdate(pos, pos, dx);
    }
    void rangeUpdate(T x, T y, const Tag &dx) {
        rangeUpdate(root, L, R, x, y, dx);
    }
    void rangeUpdate(Node* &id, T l, T r, T x, T y, const Tag &dx) {
        if(id == nullptr) id = new Node();
        if(x <= l && r <= y) {
            apply(id, dx, r - l + 1);
            return;
        }
        T mid = l + r >> 1;
        pushdown(id);
        if(x <= mid) {
            rangeUpdate(ls, l, mid, x, y, dx);
        }
        if(y > mid) {
            rangeUpdate(rs, mid + 1, r, x, y, dx);
        }
        pushup(id);
    }
    Info query(T pos) {
        return rangeQuery(pos, pos);
    }
    Info rangeQuery(T l, T r) {
        return rangeQuery(root, L, R, l, r);
    }
    Info rangeQuery(Node* &id, T l, T r, T x, T y) {
        if(id == nullptr) return Info::unit();
        if(x <= l && r <= y) {
            return id->info;
        }
        T mid = l + r >> 1;
        pushdown(id);
        Info res = Info::unit();
        if(x <= mid) {
            res = res + rangeQuery(ls, l, mid, x, y);
        }
        if(y > mid) {
            res = res + rangeQuery(rs, mid + 1, r, x, y);
        }
        return res;
    }
    void merge(SegmentTree<Info, Tag, T> seg) {
        root = merge(root, seg.root, L, R);
    }
    Node* merge(Node* &xid, Node* &yid, T l, T r) {
        if(xid == nullptr) return yid;
        if(yid == nullptr) return xid;
        if(l == r) {
            xid->info = (xid->info ^ yid->info);
            delete yid;
            return xid;
        }
        T mid = l + r >> 1;
        pushdown(xid);
        pushdown(yid);
        xid->l = merge(xid->l, yid->l, l, mid);
        xid->r = merge(xid->r, yid->r, mid + 1, r);
        pushup(xid);
        delete yid;
        return xid;
    }
    SegmentTree<Info, Tag, T> split(T l, T r) { //分裂出[l, r]的部分
        SegmentTree<Info, Tag, T> seg(L, R);
        seg.root = split(root, L, R, l, r);
        return seg;
    }
    Node* split(Node* &id, T l, T r, T x, T y) {
        if(id == nullptr || r < x || l > y) return nullptr;
        Node* nid = nullptr;
        if(x <= l && r <= y) {
            std::swap(id, nid);
            return nid;
        }
        nid = new Node();
        T mid = l + r >> 1;
        pushdown(id);
        if(x <= mid) {
            nid->l = split(ls, l, mid, x, y);
        }
        if(y > mid) {
            nid->r = split(rs, mid + 1, r, x, y);
        }
        pushup(id);
        pushup(nid);
        return nid;
    }
    T findFirst(T x, T y, auto check) {
        Info pre = Info::unit();
        return findFirst(root, L, R, x, y, pre, check);
    }
    T findFirst(Node* &id, T l, T r, T x, T y, Info& pre, auto check) {
        if(id == nullptr) return -1;
        if(x <= l && r <= y) {
            if(!check(pre + id->info)) {
                pre = pre + id->info;
                return -1;
            } else if(l == r) {
                return l;
            }
        }
        T mid = l + r >> 1;
        pushdown(id);
        if(x <= mid) {
            int res = findFirst(ls, l, mid, x, y, pre, check);
            if(res != -1) return res;
        }
        return findFirst(rs, mid + 1, r, x, y, pre, check);
    }
#undef ls
#undef rs
#undef pushdown
    T L, R;
    Node* root = nullptr;
};

struct Tag {
    Tag() = default;
    Tag(int _add) : add(_add) {}
    void apply(const Tag &dx) {
        add += dx.add;
    }
    bool operator==(const Tag&) const = default;
    int add = 0;
};

struct Info {
    Info() = default;
    Info(i64 _val) : sum(_val) {}
    template<typename T>
    void apply(const Tag &dx, const T &len) {
        sum += dx.add * len;
    }
    static Info unit() {
        return Info();
    }
    i64 sum = 0;
};

Info operator+(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}

Info operator^(const Info &x, const Info &y) {
    Info res;
    res.sum = x.sum + y.sum;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, idx = 1;
    std::cin >> n >> m;
    std::vector segs(n + 1, SegmentTree<Info, Tag, int>(MAXN + 1));
    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        segs[idx].update(i, x);
    }
    for(int i = 0; i < m; ++i) {
        int opt;
        std::cin >> opt;
        if(opt == 0) {
            int p, x, y;
            std::cin >> p >> x >> y;
            segs[++idx] = segs[p].split(x, y);
        } else if(opt == 1) {
            int p, t;
            std::cin >> p >> t;
            segs[p].merge(segs[t]);
        } else if(opt == 2) {
            int p, x, q;
            std::cin >> p >> x >> q;
            segs[p].update(q, x);
        } else if(opt == 3) {
            int p, x, y;
            std::cin >> p >> x >> y;
            std::cout << segs[p].rangeQuery(x, y).sum << '\n';
        } else if(opt == 4) {
            int p, k;
            std::cin >> p >> k;
            std::cout << segs[p].findFirst(1, n, [&](const auto& info) ->bool {
                return info.sum >= k;
            }) << '\n';
        }
    }
    return 0;
}