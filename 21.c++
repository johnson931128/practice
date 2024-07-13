#include <iostream>
#include <cmath>
using namespace std;
int grade(int n){
    if (n > 10){
        if (n > 20){
            if (n >= 40){
                return 100;
            }else{
                return 80 + (n-20)*1;
            }
        }else{
            return 60 + (n-10)*2;
        }
    }else{
        return n*6;
    }
}

int main(){
    int n;
    while(cin >> n){
        cout << grade(n) << endl;
    }
}