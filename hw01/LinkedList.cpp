#include <iostream>
#include <time.h>
#include <math.h>
#include <random>

using namespace std; 

class Node {
public:
    short data;
    Node* next;

    Node(short val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;  // 新增一個 tail 指標來追蹤鏈結串列的尾節點
    long size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // 插入元素到鏈結串列的尾部
    void push_back(short value) {
        Node* newNode = new Node(value);  // 建立新節點
        if (tail == nullptr) {  // 如果鏈結串列為空
            head = tail = newNode;  // 新節點同時作為頭和尾
        } else {
            tail->next = newNode;  // 將目前的尾節點指向新節點
            tail = newNode;        // 更新 tail 為新節點
        }
        size++;  // 增加鏈結串列的大小
    }

    long long addUp() const {
        long long total = 0;
        Node* current = head;
        while (current != nullptr) {
            total += current->data;
            current = current->next;
        }
        return total;
    }

    long getSize() const {
        return size;
    }
};

void insert(LinkedList& v, int amount) {
    clock_t start = clock();
    for (long i = 0; i < amount; i++) {
        v.push_back(rand() % 10);  // 使用 push_back 來插入隨機數據
    }
    clock_t end = clock();
    cout << "push_back took: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}

/*
// 插入每次 2^13 筆資料，重複 128 次
void insert(LinkedList& v) {
    const int chunk = pow(2, 13);  // 每次插入 2^13 筆資料
    const int total_batches = 128; // 總共進行 128 次插入
    clock_t start, end;

    for (int i = 0; i < total_batches; i++) {
        start = clock();  // 記錄插入開始時間
        for (int j = 0; j < chunk; ++j) {
            v.push_back(rand() % 10);  // 使用 push_back 插入隨機數據
        }
        end = clock();  // 記錄插入結束時間
        // 記錄每次插入所需的時間
        double duration = double(end - start) / CLOCKS_PER_SEC;
        cout << "Batch " << i + 1 << " (Inserted " << (i + 1) * chunk 
             << " elements) took: " << duration << " seconds" << endl;
    }
}
*/

void addUp(LinkedList& v) {
    clock_t start = clock();
    long long total = v.addUp();
    clock_t end = clock();
    cout << "addUp took: " << double(end - start) / CLOCKS_PER_SEC << " seconds, result: " << total << endl;
}

void run(int k) {
    long n = pow(2, k);
    cout << endl;
    cout << "k = " << k << ", n = " << n << endl;
    LinkedList v;


    insert(v, n);
    addUp(v);
}

int main() {
    srand(time(NULL));
    for (int i = 11; i <= 25; i++) {
        run(i);
    }
}
