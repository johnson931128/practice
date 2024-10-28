#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(){
	int n;
	cin >> n;
	while (n > 0){
		int odd = 0, even = 0;
		string s;
		cin >> s;
		for(int i = 0; i < s.length(); i++){
			if(i % 2 == 0){
				even += s[i] - '0'; 
			} else {
				odd += s[i] - '0';  
			}
		}
		

		if(abs(even - odd) % 11 == 0){
			cout << "Yes" << '\n';
		} else {
			cout << "No" << '\n';
		}
		n--;
	}
	
	return 0;
}

