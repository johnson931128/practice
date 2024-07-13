#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

int countPrimes(int a, int b) {
    int count = 0;
    for (int i = a; i <= b; ++i) {
        if (isPrime(i)) {
            ++count;
        }
    }
    return count;
}

int main() {
    int a, b;
    while (cin >> a >> b) {
        int primeCount = countPrimes(a, b);
        cout << primeCount << endl;
    }
    return 0;
}

