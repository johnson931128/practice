#include <iostream>
#include <string>
#include <cmath>
using namespace std;
int main(){
    //平面圓切割問題
    int n;
    while(cin >> n){
        cout << pow(n, 2) - n + 2 << endl;
    }
}