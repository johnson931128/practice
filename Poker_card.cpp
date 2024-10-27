#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Card{
	char color;
	int value;
};

Card card[52]; // card 裡面每個都是 Card struct 
char colors[4] = {'H', 'S', 'D', 'C'};
int N;

void initializeDeck(){
	int index = 0;
	for (int c = 0; c < 4; c++){
		for (int i = 1; i <= 13; i++){
			card[index].color = colors[c]; // setting the color
			card[index].value = i;
			index++;
		}
	}
}

void randomShuffle(){
	for (int i = 0; i < 52; i++){
		int j = rand() % 52;
		swap(card[i], card[j]);
	}
}

void drawCards(int N){
	for(int i = 0; i < N; i++){
		cout << card[i].color << card[i].value << " ";
	}
	cout << endl;
} 


int main(){
	srand(time(0));
	initializeDeck();
	randomShuffle();
	
	cin >> N;
	drawCards(N);
	return 0;
}








