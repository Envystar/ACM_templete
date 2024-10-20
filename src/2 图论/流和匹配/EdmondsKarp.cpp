#include <bits/stdc++.h>
using i64 = long long;

struct Edge {
    Edge() = default;
    Edge(int _nxt, int _cap, int _enxt) : nxt(_nxt), cap(_cap), enxt(_enxt) {}
    int nxt, cap, enxt;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, S, T;
    std::cin >> n >> m >> S >> T;
    std::vector<Edge> e(2 * m);
    std::vector<int> head(n + 1, -1), pre(n + 1); // pre: id的前驱边
    std::vector<int> mf(n + 1); //每S~v的流量上限, 
    for(int i = 0; i < 2 * m; i += 2) {
        int x, y, cap;
        std::cin >> x >> y >> cap;
        e[i] = Edge(y, cap, head[x]);
        head[x] = i;
        e[i ^ 1] = Edge(x, 0, head[y]);
        head[y] = i ^ 1;
    } 
    auto bfs = [&]() ->bool{
        std::fill(mf.begin(), mf.end(), 0);
        mf[S] = INT_MAX;
        std::queue<int> q;
        q.push(S);
        while(!q.empty()) {
            int id = q.front();
            q.pop();
            for(int eid = head[id]; ~eid; eid = e[eid].enxt) {
                auto &[nxt, cap, _] = e[eid];
                if(mf[nxt] == 0 && cap > 0) {
                    mf[nxt] = std::min(mf[id], cap);
                    pre[nxt] = eid;
                    if(nxt == T) return true;
                    q.push(nxt);
                }
            }
        }
        return false;
    };
    auto EK = [&]() ->i64 {
        i64 flow = 0;
        while(bfs()) { //找到增广路
            for(int id = T; id != S; id = e[pre[id] ^ 1].nxt) {
                e[pre[id]].cap -= mf[T];
                e[pre[id] ^ 1].cap += mf[T];
            }
            flow += mf[T]; 
        }
        return flow;
    };
    std::cout << EK() << '\n';
    return 0;
}