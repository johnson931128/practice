#include <iostream>
#include <stack>
using namespace std;

bool isValid(string s){
	stack<char> st;
	for (char op : s){
		if (op == '(' || op == '[' || op == '{'){
			st.push(op);
		}else {
			if (st.empty()) return false;
			
			if ((op == ')' && st.top() == '(') || (op == ']' && st.top() == '[') || (op == '}' && st.top() == '{')){
				st.pop();
			}else {
				return false;
			}
		}
	}
	return st.empty();
}


int main(){
	string s;
	cin >> s;
	bool result = isValid(s);
	cout << (result ? "true" : "false") << endl;
	return 0;
}
