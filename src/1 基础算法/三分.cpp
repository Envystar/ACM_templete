#include <bits/stdc++.h>
constexpr double eps = 1E-6;//eps控制精度

//三分（实数范围）凸函数
//https://www.luogu.com.cn/record/160695683
int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    double l, r;
    std::cin >> n >> l >> r;
    std::vector<double> v(n + 1);
    for(int i = n; i >= 0; --i) {
        std::cin >> v[i];
    }
    auto check = [&](double t) ->double {
        double ans = 0;
        for(int i = 0; i <= n; ++i) {
            ans += v[i] * std::pow(t, i);
        }
        return ans;
    };
    while(l + eps <= r) { 
        double lmid = l + (r - l) / 3;//左三分点
        double rmid = r - (r - l) / 3;//右三分点
        if(check(lmid) < check(rmid)) {
            l = lmid;
        } else {
            r = rmid;
        }
    }
    std::cout << l << '\n';
    return 0;
}