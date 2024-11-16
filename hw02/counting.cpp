#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// 計數排序的實作
void countingSort(vector<int>& arr, int maxVal) {
    int n = arr.size();

    // 創建計數陣列
    vector<int> count(maxVal + 1, 0);

    // 計算每個元素的出現次數
    for (int i = 0; i < n; ++i) {
        count[arr[i]]++;
    }

    // 將計數結果反映到原陣列中
    int index = 0;
    for (int i = 0; i <= maxVal; ++i) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }
}

// 主程式
int main() {
    // 設定隨機種子
    srand(time(0));

    // 進行 n = 2^10 到 2^30 的排序測試
    for (int exp = 10; exp <= 30; ++exp) {
        int n = pow(2, exp);
        vector<int> arr(n);

        // 生成隨機陣列，元素範圍為 0 到 n-1
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % n;
        }

        // 記錄排序前的時間
        auto start = high_resolution_clock::now();

        // 進行計數排序
        countingSort(arr, n - 1);

        // 記錄排序後的時間
        auto stop = high_resolution_clock::now();

        // 計算排序時間，將毫秒轉換為秒
        auto duration = duration_cast<milliseconds>(stop - start);
        double durationInSeconds = duration.count() / 1000.0;

        // 輸出結果
        cout << "n = 2^" << exp << " (" << n << " elements), Sorting time: " 
             << durationInSeconds << " seconds" << endl;
    }

    return 0;
}
