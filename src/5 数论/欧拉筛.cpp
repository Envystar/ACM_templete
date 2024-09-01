#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<bool> isPrime(n + 1, 1);
    std::vector<int> res = {2}; //存放质数
    isPrime[0] = 0;
    for (int i = 3; i <= n; i += 2) {
        if (isPrime[i]) { //如果是素数, 则记录
            res.push_back(i);
        }
        for (int j = 0; res[j] * i <= n && j < res.size(); ++j) {
            isPrime[res[j] * i] = 0;//找出素数的倍数，标记为合数
            if (i % res[j] == 0) break;          
        }
    }
    std::cout << res.size() << '\n';
    for(auto x : res) {
        std::cout << x << ' ';
    }
    return 0;
}

