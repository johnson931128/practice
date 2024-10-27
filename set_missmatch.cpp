#include <iostream>
#include <vector>
#include <unordered_map> // use to find the same number of nums
using namespace std;

vector<int> findErrorNums(vector<int>& nums) {
    unordered_map<int, int> count;
    vector<int> result(2);

    for (int a : nums) {
        count[a]++;
    }

    for (int i = 1; i <= nums.size(); i++) {
        if (count[i] == 2) { // 找到重複的數字
            result[0] = i;
        }
        else if (count[i] == 0) { // 找到缺失的數字
            result[1] = i;
        }
    }
    return result;
}

int main() {
    int ele;
    vector<int> nums;

    cout << "請輸入一組數字，按Enter結束：" << endl;
    while (cin >> ele) {
        if (cin.peek() == '\n') break;
        nums.push_back(ele);
    }

    vector<int> result = findErrorNums(nums);

    // 正確輸出格式 [重複的數字, 缺失的數字]
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;

    return 0;
}

