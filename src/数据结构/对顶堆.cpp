#include <bits/stdc++.h>
using i64 = long long;

//对顶堆，维护第k小/大
template<typename T>
struct DoubleHeap {
    DoubleHeap(int _k) : k(_k) {} //第k小, 若要第k大，将下面比较函数反转
    std::priority_queue<T, std::vector<T>, std::less<T>> mpq; //大根堆[1, k - 1]
    std::priority_queue<T, std::vector<T>, std::greater<T>> Mpq; //小根堆[k, sz]
    void insert(T x) {
        mpq.push(x);
        while(mpq.size() >= k) {
            Mpq.push(mpq.top());
            mpq.pop();
        }
    }
    T kth() {
        assert(Mpq.empty() == false);
        return Mpq.top();
    }
    const int k;
};

struct MINT {
    int x;
    bool operator<(const MINT &o) const {
        return x < o.x;
    }
    bool operator>(const MINT &o) const {
        return x > o.x;
    }
};

void solve() {
    int n, k;
    std::cin >> n >> k;
    DoubleHeap<MINT> dpq(k);
    for(int i = 1; i <= n; ++i) {
        int opt;
        std::cin >> opt;
        if(opt == 1) {
            int x;
            std::cin >> x;
            dpq.insert({x});
        } else {
            std::cout << dpq.kth().x << '\n';
        }
    }

}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int T;
    std::cin >> T;
    while(T--) {
        solve();
    }
    return 0;
}