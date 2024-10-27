#include <iostream>
#include <vector>
using namespace std;

vector<int> queue;
int i = -1;
int f = -1;

// 使用 vector 實現 queue
void push(int value) {
    queue.push_back(value);
    f++;
}

void pop() {
    if (queue.empty()) {
        cout << "No element" << endl;
    } else {
        cout << queue[0] << endl;  // 列印隊列中的第一個元素
        queue.erase(queue.begin());  // 移除隊列的第一個元素
   		i++;
    }
}

int main() {
    push(10);
    push(20);
    push(30);
    cout << queue[f] << endl;
    pop();  // 應該列印 10
    pop();  // 應該列印 20
    cout << queue[i] << endl;
    pop();  // 應該列印 30
    pop();  // "No element"（因為已經空了）
    return 0;
}


