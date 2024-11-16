#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

// 三向隨機化分區
void threeWayPartition(vector<int>& arr, int low, int high, int& lt, int& gt) {
    int pivot = arr[low]; // 使用最左邊的元素作為樞軸
    lt = low;             // lt 為小於樞軸部分的邊界
    gt = high;            // gt 為大於樞軸部分的邊界
    int i = low + 1;      // 掃描當前元素的指標

    while (i <= gt) {
        if (arr[i] < pivot) {
            swap(arr[lt], arr[i]);
            lt++;
            i++;
        } else if (arr[i] > pivot) {
            swap(arr[i], arr[gt]);
            gt--;
        } else {
            i++;
        }
    }
}

// 隨機化三向分區
void randomizedThreeWayPartition(vector<int>& arr, int low, int high, int& lt, int& gt) {
    int randomPivotIndex = low + rand() % (high - low + 1);
    swap(arr[low], arr[randomPivotIndex]); // 隨機選擇樞軸並將其換到最左邊
    threeWayPartition(arr, low, high, lt, gt); // 使用三向分區法
}

// 隨機化三向快速排序
void randomizedQuickSort3Way(vector<int>& arr, int low, int high) {
    if (low < high) {
        int lt, gt;
        randomizedThreeWayPartition(arr, low, high, lt, gt);
        randomizedQuickSort3Way(arr, low, lt - 1);  // 對小於樞軸部分排序
        randomizedQuickSort3Way(arr, gt + 1, high); // 對大於樞軸部分排序
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

        // 進行隨機化三向快速排序
        randomizedQuickSort3Way(arr, 0, n - 1);

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