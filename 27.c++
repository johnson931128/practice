#include <iostream>
#include <vector>
#include <algorithm>  // 為了使用 std::sort
using namespace std;

void sortAndPrint(vector<int> &v) {
    // 使用標準庫中的 sort 函數進行排序
    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        if (i != 0) {
            cout << " ";
        }
        cout << v[i];
    }
    cout << endl;
}

int main() {
    vector<int> v;  // vector 是一個動態陣列
    int n;
    while (cin >> n) {
        v.clear();  // 清空 vector
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            v.push_back(x);
        }
        sortAndPrint(v);
    }
    return 0;
}


