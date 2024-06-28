#include <iostream>
using namespace std;

int main() {
    int m;
    while (cin >> m) { // 直接在這裡檢查輸入是否成功
        if (m % 4 == 0 && m % 100 != 0 || m % 400 == 0)
            cout << "閏年\n" << endl;
        else
            cout << "平年\n" << endl;
    }
    return 0;
}