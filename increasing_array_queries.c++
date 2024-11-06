#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1), diff(n); // arr: 原始陣列, diff: 需要增長的差異陣列

    // 讀取陣列
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }

    // 計算 diff 陣列
    vector<long long> prefixSum(n + 1, 0); // prefixSum 用來儲存前綴和
    for (int i = 2; i <= n; i++)
    {
        if (arr[i] < arr[i - 1])
        {
            diff[i - 1] = arr[i - 1] - arr[i];
        }
        prefixSum[i] = prefixSum[i - 1] + diff[i - 1];
    }

    // 處理查詢
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        // 查詢區間 [a, b] 需要多少增長操作
        if (a == b)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << prefixSum[b - 1] - prefixSum[a - 1] << endl;
        }
    }

    return 0;
}
