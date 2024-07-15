#include <iostream>
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        int sum = n, i;
        for (i = 1; sum <= m; i++) {
            sum += n + i;
        }
        cout << i << endl;
    }
    return 0;
}

