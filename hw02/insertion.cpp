#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// 插入排序的實作
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main() {
    srand(time(0));

    for (int exp = 10; exp <= 30; ++exp) {
        int n = pow(2, exp);
        vector<int> arr(n);

        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % n;
        }

        // 記錄排序前的時間
        auto start = high_resolution_clock::now();

        // 各類排序
        insertionSort(arr);
        //mergeSort(arr, 0, n - 1);
        //randomizedQuickSort(arr, 0, n - 1); //for hoare
        //countingSort(arr, n - 1);
        //randomizedQuickSort(arr, 0, n - 1); //for lomuto
        //randomizedQuickSort3Way(arr, 0, n - 1);

        // 記錄排序後的時間
        auto stop = high_resolution_clock::now();

        // 計算排序時間（毫秒轉換為秒）
        auto duration = duration_cast<milliseconds>(stop - start);
        double durationInSeconds = duration.count() / 1000.0;  // 毫秒轉換為秒

        // 輸出結果
        cout << "n = 2^" << exp << " (" << n << " elements), Sorting time: " 
             << durationInSeconds << " seconds" << endl;
    }

    return 0;
}