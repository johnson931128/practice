#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

int three(vector<int> a){
    int count1 = 0;
    int count2 = 0;
    int count3 = 0;
    for (int i = 0; i < a.size(); i++){
        if (a[i] % 3 == 0){
            count1++;
        }
        if (a[i] % 3 == 1){
            count2++;
        }
        if (a[i] % 3 == 2){
            count3++;
        }
    }
    cout << count1 << " " << count2 << " " << count3 << endl;
}

int main(){
    int n = 0;
    int m;
    cin >> n;
    vector<int> a;
    while (n > 0){
        cin >> m;
        a.push_back(m);
        n--;
    }
    three(a);
}