#include <bits/stdc++.h>
using i64 = long long;
using u32 = uint32_t;
using u64 = uint64_t;

struct BitRank {
    std::vector<u64> block; // 管理一行一行的bit
    std::vector<u32> count;
    BitRank() {}
    
    void resize(u32 num) { // 位向量长度
        block.resize(((num + 1) >> 6) + 1, 0);
        count.resize(block.size(), 0);
    }
    void set(u32 i, u64 val) { // 设置i位bit
        block[i >> 6] |= (val << (i & 63));
    }
    void build() {
        for (u32 i = 1; i < block.size(); i++) {
            count[i] = count[i - 1] + std::popcount(block[i - 1]);
        }
    }
    u32 rank1(u32 i) { // [0, i) 1的个数
        return count[i >> 6] + std::popcount(block[i >> 6] & ((1ULL << (i & 63)) - 1ULL));
    }
    u32 rank1(u32 i, u32 j) { // [i, j) 1的个数
        return rank1(j) - rank1(i);
    }
    u32 rank0(u32 i) { // [0, i) 0的个数
        return i - rank1(i);
    }
    u32 rank0(u32 i, u32 j) { // [i, j) 0的个数
        return rank0(j) - rank0(i);
    }
};

template<typename T> //要求非负整数
struct WaveletMatrix {
    WaveletMatrix() = default;
    WaveletMatrix(std::vector<T> vec) : WaveletMatrix(vec, std::ranges::max(vec) + 1) {}
    // sigma: 字母表大小(字符串的话)，数字序列的话是数的种类
    WaveletMatrix(std::vector<T> vec, T sigma) {
        height = (sigma == 1) ? 1 : (64 - std::countl_zero<u64>(sigma - 1));
        B.resize(height), pos.resize(height);
        for (u32 i = 0; i < height; ++i) {
            B[i].resize(vec.size());
            for (u32 j = 0; j < vec.size(); ++j) {
                B[i].set(j, get(vec[j], height - i - 1));
            }
            B[i].build();
            auto it = stable_partition(vec.begin(), vec.end(), [&](T c) {
                return !get(c, height - i - 1);
            });
            pos[i] = it - vec.begin();
        }
    }
    T get(T val, int i) {
        return (val >> i) & 1;
    }
    int rank(int l, int r, T val) { // [l, r] 中val出现的频率
        return rank(r, val) - rank(l - 1, val);
    }
    int rank(int i, T val) { // [0, i] 中val出现的频率
        ++i;
        int p = 0;
        for (u32 j = 0; j < height; ++j) {
            if (get(val, height - j - 1)) {
                p = pos[j] + B[j].rank1(p);
                i = pos[j] + B[j].rank1(i);
            } else {
                p = B[j].rank0(p);
                i = B[j].rank0(i);
            }
        }
      return i - p;
    }
    T kth(int l, int r, int k) { // [l, r] 中k小
        ++r;
        T res = 0;
        for (u32 i = 0; i < height; ++i) {
            int j = B[i].rank0(l, r);
            if (j >= k) {
                l = B[i].rank0(l);
                r = B[i].rank0(r);
            } else {
                l = pos[i] + B[i].rank1(l);
                r = pos[i] + B[i].rank1(r);
                k -= j;
                res |= (T(1) << (height - i - 1));
            }
      }
      return res;
    }
    int rangeFreq(int l, int r, T a, T b) {  // [l,r] 在[a, b] 值域的数字个数
        return rangeFreq(l, r + 1, a, b + 1, 0, T(1) << height, 0);
    }
    int rangeFreq(int i, int j, T a, T b, T l, T r, int x) {
        if (i == j || r <= a || b <= l) return 0;
        T mid = (l + r) >> 1;
        if (a <= l && r <= b) {
            return j - i;
        } else {
            int left = rangeFreq(B[x].rank0(i), B[x].rank0(j), a, b, l, mid, x + 1);
            int right = rangeFreq(pos[x] + B[x].rank1(i), pos[x] + B[x].rank1(j), a, b, mid, r, x + 1);
            return left + right;
        }
    }
    // [l,r] 在[a,b] 值域内存在的最小值是什么，不存在返回-1
    T rangeMin(int l, int r, T a, T b) {
        return rangeMin(l, r + 1, a, b + 1, 0, T(1) << height, 0, 0);
    }
    T rangeMin(int i, int j, T a, T b, T l, T r, int x, T val) {
        if (i == j || r <= a || b <= l) return -1;
        if (r - l == 1) return val;
        T mid = (l + r) >> 1;
        T res = rangeMin(B[x].rank0(i), B[x].rank0(j), a, b, l, mid, x + 1, val);
        if (res >= 0) return res;
        return rangeMin(pos[x] + B[x].rank1(i), pos[x] + B[x].rank1(j), a, b, mid, r, x + 1, val + (T(1) << (height - x - 1)));
    }
    T rangeMax(int l, int r, T a, T b) {
        return rangeMax(l, r + 1, a, b + 1, 0, T(1) << height, 0, 0);
    }
    T rangeMax(int i, int j, T a, T b, T l, T r, int x, T val) {
        if (i == j || r <= a || b <= l) return -1;
        if (r - l == 1) return val;
        T mid = (l + r) >> 1;
        T res = rangeMax(pos[x] + B[x].rank1(i), pos[x] + B[x].rank1(j), a, b, mid, r, x + 1, val + (T(1) << (height - x - 1)));
        if (res >= 0) return res;
        return rangeMax(B[x].rank0(i), B[x].rank0(j), a, b, l, mid, x + 1, val);
    }
    u32 height;
    std::vector<BitRank> B;
    std::vector<int> pos;
};

//波纹疾走树(区间第k小， 区间val出现的频率，区间在值域出现的次数和最小值)
//https://www.luogu.com.cn/problem/P3834
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<i64> v(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> v[i];
    }
    WaveletMatrix<i64> wlm(v);
    for(int i = 1; i <= q; ++i) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << wlm.kth(l, r, k) << '\n';
    }
    return 0;
}