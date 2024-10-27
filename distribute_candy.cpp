 /* n candies; 
 	n is even;
 	i^th candy -> candyType[i];
*/
#include <iostream>
#include <vector>
#include <set> // use to find different type of integers
using namespace std;


int how_many_type(vector<int> candyType){
	int n = candyType.size();
	set<int> uniqueType(candyType.begin(), candyType.end());
	int types = uniqueType.size();
	int can_eat = n/2;
	if(can_eat == types || can_eat > types) return types;
	else if(can_eat < types) return can_eat;
}

int main(){
	int num;
	vector<int> candyType;

	while (cin >> num) {
        candyType.push_back(num); // 將輸入的數字加入到 vector
        if (cin.peek() == '\n') break; // 如果遇到換行符，結束輸入
    }
	int result = how_many_type(candyType);
	cout << result << endl;
	return 0;
}
