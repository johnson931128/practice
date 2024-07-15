#include <iostream>
using namespace std;
int main(){
    int T;
    cin >> T;
    while (T--){
        unsigned int n; // 0~2^32-1
        cin >> n;
        int product = 1;
        if (n == 0){product = 0;}
        while (n != 0){
            product *= n % 10;
            n /= 10; //here n is a unsigned int, so n/10 will be 0 when n < 10，取商
        }
        cout << product << endl;
    }
    return 0;
}