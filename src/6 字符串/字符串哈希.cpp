#include <bits/stdc++.h>
using i64 = long long;

//字符串hash
//https://www.luogu.com.cn/problem/P3370
struct Hash {
    std::vector<i64> h1, p1, h2, p2;
    const i64 base1 = 31, base2 = 37;
    const i64 mod1 = 2013265921, mod2 = 1004535809;
    Hash(const std::string &s) //0-index
    : n(s.size()), h1(s.size() + 1), h2(s.size() + 1), p1(s.size() + 1), p2(s.size() + 1) {
        p1[0] = p2[0] = 1;
        for (i64 i = 1; i <= n; i++) {
            p1[i] = p1[i - 1] * base1 % mod1;
            p2[i] = p2[i - 1] * base2 % mod2;
        }
        for (i64 i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * base1 % mod1 + s[i - 1]) % mod1;
            h2[i] = (h2[i - 1] * base2 % mod2 + s[i - 1]) % mod2;
        }
    }
    std::pair<i64, i64> get(int l, int r) {//1-index
        i64 hash1 = (h1[r] - h1[l - 1] * p1[r - l + 1] % mod1 + mod1) % mod1;
        i64 hash2 = (h2[r] - h2[l - 1] * p2[r - l + 1] % mod2 + mod2) % mod2;
        return {hash1, hash2};
    }
    int n;
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::set<std::pair<i64, i64>> st;
    for(int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        Hash hs(s);
        st.insert(hs.get(1, s.size()));
    }
    std::cout << st.size() << '\n';
    return 0;
}