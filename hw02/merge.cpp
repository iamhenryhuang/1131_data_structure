#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// 合併兩個子陣列
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1), rightArr(n2);

    // 複製資料到暫存陣列
    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            ++i;
        } else {
            arr[k] = rightArr[j];
            ++j;
        }
        ++k;
    }

    // 複製剩餘的元素
    while (i < n1) {
        arr[k] = leftArr[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        ++j;
        ++k;
    }
}

// 合併排序的遞迴函式
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // 遞迴排序兩個子陣列
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // 合併兩個已排序的子陣列
        merge(arr, left, mid, right);
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

        // 進行合併排序
        mergeSort(arr, 0, n - 1);

        // 記錄排序後的時間
        auto stop = high_resolution_clock::now();

        // 計算排序時間，轉換為秒
        auto duration = duration_cast<milliseconds>(stop - start);
        double durationInSeconds = duration.count() / 1000.0;

        // 輸出結果
        cout << "n = 2^" << exp << " (" << n << " elements), Sorting time: " 
             << durationInSeconds << " seconds" << endl;
    }

    return 0;
}
