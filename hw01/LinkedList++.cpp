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
    long size;

public:
    LinkedList() : head(nullptr), size(0) {}

    // 插入元素並按數據排序 
    void insert_sorted(short value) {
        Node* newNode = new Node(value);
        if (head == nullptr || head->data >= value) {
            // 如果鏈結串列為空或新節點數據比頭節點小，直接插入到頭部
            newNode->next = head;
            head = newNode;
        } else {
            // 否則找到適合的位置進行插入
            Node* current = head;
            while (current->next != nullptr && current->next->data < value) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
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
        v.insert_sorted(rand() % 10);  // 使用有序插入方式插入隨機數據
    }
    clock_t end = clock();
    cout << "insert_sorted took: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}

/*
// 插入每次 2^13 資料的函數，總共執行 128 次
void insert(LinkedList& v) {
    const int chunk = pow(2, 13);  // 每次插入 2^13 筆資料
    const int total_batches = 128; // 總共插入 128 次
    clock_t start, end;

    for (int i = 0; i < total_batches; i++) {
        start = clock();  // 記錄插入開始時間
        for (int j = 0; j < chunk; ++j) {
            v.insert_sorted(rand() % 10);  // 使用有序插入方式插入隨機數據
        }
        end = clock();  // 記錄插入結束時間
        // 記錄每次插入的時間
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
