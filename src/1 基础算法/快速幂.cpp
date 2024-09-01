#include <bits/stdc++.h>
using i64 = long long;

//快速幂（Binary Exponentiation)
i64 qpow(i64 a, i64 b, i64 p = LLONG_MAX) { //底数，指数, 模数
    i64 res = 1;
    while(b > 0) {
        if(b & 1) res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << qpow(2, 20) << '\n';
    std::cout << std::pow(2, 20) << '\n';
    return 0;
}