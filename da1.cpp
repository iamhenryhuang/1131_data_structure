#include<iostream>
#include<time.h>
#include<math.h>

using namespace std;

class DynamicArray {
    short* arr;
    long capacity;
    long size;

public:
    DynamicArray() : capacity(1), size(0) {
        arr = new short[capacity];
    }

    ~DynamicArray() {
        delete[] arr;
    }

    void push_back(short value) {
        if (size == capacity) {
            resize();
        }
        arr[size++] = value;
    }

    long long addUp() const {
        long long total = 0;
        for (long i = 0; i < size; i++) {
            total += arr[i];
        }
        return total;
    }

    long getSize() const {
        return size;
    }

    long getCapacity() const {
        return capacity;
    }

private:
    void resize() {
        long new_capacity = capacity * 2;  // 增加容量的方式改為乘以2
        short* new_arr = new short[new_capacity];
        for (long i = 0; i < size; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        capacity = new_capacity;
    }
};

void push(DynamicArray& d, int amount) {
    clock_t start = clock();
    for (long i = 0; i < amount; i++) {
        d.push_back(rand() % 10);
    }
    clock_t end = clock();
    // 計算時間並轉換為秒
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "push took: " << duration << " seconds" << endl;
}

void addUp(DynamicArray& d) {
    clock_t start = clock();
    long long total = d.addUp();
    clock_t end = clock();
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "addUp took: " << duration << " seconds, result: " << total << endl;
}

// 插入每次 2^13 筆資料，總共進行 128 次
/*void push(DynamicArray& d) {
    const int chunk = pow(2, 13);  // 每次插入的資料數量
    const int total_batches = 128; // 總共插入 128 次
    clock_t start, end;

    for (int i = 0; i < total_batches; i++) {
        start = clock();  // 記錄插入開始時間
        for (int j = 0; j < chunk; ++j) {
            d.push_back(rand() % 10);
        }
        end = clock();  // 記錄插入結束時間
        // 計算每次插入所花費的時間並轉換為秒
        double duration = double(end - start) / CLOCKS_PER_SEC;
        cout << "Batch " << i + 1 << " (Inserted " << (i + 1) * chunk 
             << " elements) took: " << duration << " seconds" << endl;
    }
}*/

void run(int k) {
    long n = pow(2, k);
    cout << endl;
    cout << "k = " << k << ", n = " << n << endl;
    DynamicArray d;
    //LinkedList v;

    push(d, n);
    addUp(d);
}

int main() {
    srand(time(NULL));
    for (int i = 11; i <= 25; i++) {
        run(i);
    }
}
