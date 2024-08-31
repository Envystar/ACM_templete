#include <bits/stdc++.h>

//二分查找
//https://www.luogu.com.cn/record/160694930
int binaryFind(std::vector<int> &v, int t) {
    int l = 1, r = v.size() - 1, ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(v[mid] >= t) { //此处可换成check函数
            r = mid - 1;
            if(v[mid] == t) { //判断什么时候更新答案
                ans = mid;
            }
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> v[i];
    }
    for(int i = 1; i <= m; ++i) {
        int x;
        std::cin >> x;
        std::cout << binaryFind(v, x) << " \n"[i == m];
    }
    return 0;
}