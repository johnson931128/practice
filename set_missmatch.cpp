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
        if (count[i] == 2) { // ��쭫�ƪ��Ʀr
            result[0] = i;
        }
        else if (count[i] == 0) { // ���ʥ����Ʀr
            result[1] = i;
        }
    }
    return result;
}

int main() {
    int ele;
    vector<int> nums;

    cout << "�п�J�@�ռƦr�A��Enter�����G" << endl;
    while (cin >> ele) {
        if (cin.peek() == '\n') break;
        nums.push_back(ele);
    }

    vector<int> result = findErrorNums(nums);

    // ���T��X�榡 [���ƪ��Ʀr, �ʥ����Ʀr]
    cout << "[" << result[0] << ", " << result[1] << "]" << endl;

    return 0;
}
