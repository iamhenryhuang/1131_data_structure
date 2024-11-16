#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// 插入排序實作
void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 合併排序
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (int i = 0; i < temp.size(); ++i) arr[left + i] = temp[i];
}

// 合併排序的遞迴部分
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Quick_Merge_Sort_s 的遞迴實作
void quickMergeSort(vector<int>& arr, int left, int right, int threshold) {
    if (right - left + 1 <= threshold) {
        mergeSort(arr, left, right);
        return;
    }

    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    int pi = i + 1;

    quickMergeSort(arr, left, pi - 1, threshold);
    quickMergeSort(arr, pi + 1, right, threshold);
}

int main() {
    srand(time(0));
    int s = 3;  // 根據需求調整s的值 (如 1, 2, 3, 4, 5)
    int threshold = pow(10, s);  // 計算閾值

    for (int exp = 10; exp <= 30; ++exp) {  // 減少至 2^20 測試以避免時間過長
        int n = pow(2, exp);
        vector<int> arr(n);
        
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % n;
        }

        auto start = high_resolution_clock::now();

        quickMergeSort(arr, 0, n - 1, threshold);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        double durationInSeconds = duration.count() / 1000.0;

        cout << "n = 2^" << exp << " (" << n << " elements), Sorting time: " 
             << durationInSeconds << " seconds" << endl;
    }

    return 0;
}
