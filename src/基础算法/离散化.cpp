#include <bits/stdc++.h>

//离散化 
int main() {
    std::vector<int> arr = {1000, 500, 9999, 200, 356, 200};
    std::vector<int> tmp(arr);
    std::sort(tmp.begin(), tmp.end()); //排序
    tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());//去重
    for (int i = 0; i < arr.size(); ++i) { //替换
        arr[i] = std::lower_bound(tmp.begin(), tmp.end(), arr[i]) - tmp.begin() + 1;
    } 
    for(int i= 0; i < arr.size(); ++i) {
        std::cout << arr[i] << ' ';
    }
    return 0;
}
