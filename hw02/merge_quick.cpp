#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

// Quick Sort 的實作
int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pi = partition(arr, left, right);
        quickSort(arr, left, pi - 1);
        quickSort(arr, pi + 1, right);
    }
}

// 合併步驟
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

// Merge_Quick_Sort_s 的遞迴實作
void mergeQuickSort(vector<int>& arr, int left, int right, int threshold) {
    if (right - left + 1 <= threshold) {
        quickSort(arr, left, right);
        return;
    }

    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeQuickSort(arr, left, mid, threshold);
        mergeQuickSort(arr, mid + 1, right, threshold);
        merge(arr, left, mid, right);
    }
}

int main() {
    srand(time(0));
    int s = 5; 
    int threshold = pow(10, s);  // 計算閾值

    for (int exp = 10; exp <= 30; ++exp) {
        int n = pow(2, exp);
        vector<int> arr(n);
        
        for (int i = 0; i < n; ++i) {
            arr[i] = rand() % n;
        }

        auto start = high_resolution_clock::now();

        mergeQuickSort(arr, 0, n - 1, threshold);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        double durationInSeconds = duration.count() / 1000.0;

        cout << "n = 2^" << exp << " (" << n << " elements), Sorting time: " 
             << durationInSeconds << " seconds" << endl;
    }

    return 0;
}
