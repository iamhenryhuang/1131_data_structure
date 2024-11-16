#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Hoare 分區法
int hoarePartition(vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // 選擇最左邊的元素作為樞軸
    int i = low - 1;
    int j = high + 1;

    while (true) {
        // 向右尋找比樞軸大的元素
        do {
            i++;
        } while (arr[i] < pivot);

        // 向左尋找比樞軸小的元素
        do {
            j--;
        } while (arr[j] > pivot);

        // 如果 i 和 j 相遇或交錯，返回 j
        if (i >= j)
            return j;

        // 交換 arr[i] 和 arr[j]
        swap(arr[i], arr[j]);
    }
}

// 隨機化分區，將隨機樞軸換到最左邊
int randomizedPartition(vector<int>& arr, int low, int high) {
    int randomPivotIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[randomPivotIndex]);
    return hoarePartition(arr, low, high);
}

// 隨機化快速排序
void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pivot);
        randomizedQuickSort(arr, pivot + 1, high);
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

        // 進行隨機化快速排序
        randomizedQuickSort(arr, 0, n - 1);

        // 記錄排序後的時間
        auto stop = high_resolution_clock::now();

        // 計算排序時間，將毫秒轉換為秒
        auto duration = duration_cast<milliseconds>(stop - start);
        double durationInSeconds = duration.count() / 1000.0;  // 將毫秒轉換為秒

        // 輸出結果
        cout << "n = 2^" << exp << " (" << n << " elements), Sorting time: " 
             << durationInSeconds << " seconds" << endl;
    }

    return 0;
}
