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
        long new_capacity = capacity + 1;
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
    // 計算時間並轉換為秒
    double duration = double(end - start) / CLOCKS_PER_SEC;
    cout << "addUp took: " << duration << " seconds, result: " << total << endl;
}

void run(int k) {
    long n = pow(2, k);
    cout << endl;
    cout << "k = " << k << ", n = " << n << endl;
    DynamicArray d;

    push(d, n);
    addUp(d);
}

int main() {
    srand(time(NULL));
    for (int i = 11; i <= 25; i++) {
        run(i);
    }
}