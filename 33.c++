#include <iostream>
#include <cmath>
using namespace std;

int f_function(int f){
    if (f == 1){
        return 1;
    }else{
        return f + f_function(f - 1);
    }
}

int g_function(int n){
    if (n == 1){
        return 1;
    }else{
        return f_function(n) + g_function(n - 1);
    }
}

int main(){
    int n;
    while(cin >> n){
        
        cout << f_function(n) << " " << g_function(n) << endl;
    }  
}