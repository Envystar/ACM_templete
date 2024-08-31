#include <bits/stdc++.h>

//ST表(sparseTable)
//https://www.luogu.com.cn/problem/P3865
template<typename T>
class ST { //下标从0开始
public:
    ST(const std::vector<T> &v) { //数据 
        int k = std::__lg(v.size());
        st = std::vector<std::vector<T>>(k + 1, std::vector<T>(v.size()));
        st[0] = v;
        for(int i = 0; i < k; ++i) {
            for(int j = 0; j + (1 << (i + 1)) - 1 < v.size(); ++j) {
                st[i + 1][j] = std::max(st[i][j], st[i][j + (1 << i)]);
            }
        }
    }
    T query(int l, int r) { //查询[l, r]的最大值
        int t = std::__lg(r - l + 1);
        return std::max(st[t][l], st[t][r + 1 - (1 << t)]);
    }
private:
    std::vector<std::vector<T>> st;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    ST<int> st(v);
    while(q--) {
        int l, r;
        std::cin >> l >> r;
        l--, r--;
        std::cout << st.query(l, r) << '\n';
    }
    return 0;
}