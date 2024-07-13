#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int T;
    cin >> T;  // 讀取測試資料的數量

    for (int t = 1; t <= T; ++t) {
        int a, b;
        cin >> a >> b;

        int sum = 0;
        int start = ceil(sqrt(a));  // 從 sqrt(a) 向上取整
        int end = floor(sqrt(b));   // 到 sqrt(b) 向下取整

        for (int i = start; i <= end; ++i) {
            sum += i * i;  // 計算完全平方數的和
        }

        cout << "Case " << t << ": " << sum << endl;
    }

    return 0;
}
