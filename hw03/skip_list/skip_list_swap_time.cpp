#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;
using namespace chrono;

// 節點結構
struct SkipListNode {
    int key;
    vector<SkipListNode*> forward; // forward 指針向量

    SkipListNode(int k, int level) : key(k), forward(level, nullptr) {}
};

// Skip List 結構
class SkipList {
private:
    int maxLevel;
    float probability;
    SkipListNode* header;

    int randomLevel() {
        int level = 1;
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLvl, float prob) : maxLevel(maxLvl), probability(prob) {
        header = new SkipListNode(-1, maxLevel); // -1 表示頭節點
    }

    void insert(int key) {
        vector<SkipListNode*> update(maxLevel, nullptr);
        SkipListNode* current = header;

        // 找到要插入的位置
        for (int i = maxLevel - 1; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->key < key) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        // 插入新的節點
        int level = randomLevel();
        SkipListNode* newNode = new SkipListNode(key, level);

        for (int i = 0; i < level; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    ~SkipList() {
        SkipListNode* current = header;
        while (current) {
            SkipListNode* next = current->forward[0];
            delete current;
            current = next;
        }
    }
};

int main() {
    const int n = 1 << 20; // 2^20
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;

    mt19937 rng(random_device{}());
    vector<double> avgTimes(21, 0.0);

    for (int exp = 0; exp <= 20; ++exp) {
        int k = 1 << exp; // 2^exp
        double totalTime = 0.0;

        for (int t = 0; t < 10; ++t) { // 進行 10 次測試
            vector<int> tempArr = arr;

            // 隨機交換 k 次
            for (int i = 0; i < k; ++i) {
                int idx1 = rng() % n;
                int idx2 = rng() % n;
                swap(tempArr[idx1], tempArr[idx2]);
            }

            SkipList skipList(32, 0.5); // 最大層數 32，概率 0.5
            auto start = high_resolution_clock::now(); // 開始計時

            // 插入元素到 Skip List
            for (int val : tempArr) {
                skipList.insert(val);
            }

            auto end = high_resolution_clock::now(); // 結束計時
            totalTime += duration_cast<nanoseconds>(end - start).count() / 1e9; // 秒為單位
        }

        avgTimes[exp] = totalTime / 10;
        cout << "k = 2^" << exp << ", Average Time = " << avgTimes[exp] << " seconds" << endl;
    }

    return 0;
}
