#include <iostream>
using namespace std;

int n, ans = 0, put[100], visited[3][100];

void search(int now){
	if(now == n){
		ans++;
	}else {
		for (int i = 0; i < n; i++){
			if(!visited[0][i] && !visited[1][now + i] && !visited[2][now - i + n]){
				put[now] = i;
				visited[0][i] = visited[1][now + i] = visited[2][now - i + n] = 1;
				search(now + 1);
				visited[0][i] = visited[1][now + i] = visited[2][now - i + n] = 0;
			}
		}
	}
} 

int main(){
	cin >> n;
	search(0);
	cout << ans << "\n";
}
