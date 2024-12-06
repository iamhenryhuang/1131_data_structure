#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

// 定義節點結構
struct SkipListNode {
    int val;
    vector<SkipListNode*> forward; // 向前的指針陣列

    SkipListNode(int x, int level) : val(x), forward(level, nullptr) {}
};

// 定義 SkipList 結構
struct SkipList {
    int maxLevel;            // 最大層數
    SkipListNode* head;      // SkipList 的頭節點

    SkipList(int maxLevel) {
        this->maxLevel = maxLevel;
        head = new SkipListNode(-1, maxLevel); // 建立虛擬頭節點
    }
};

// 決定節點層數的函數 (基於銅板結果)
int GetLevelFromCoinToss(const string& coinToss) {
    int level = 1; // 至少一層
    for (char c : coinToss) {
        if (c == 'H') {
            level++;
        } else {
            break; // 遇到 T 結束計算
        }
    }
    return level;
}

// 創建一個節點
SkipList* CreateSkipList(int maxLevel) {
    return new SkipList(maxLevel);
}

// 插入節點到 SkipList
void InsertSkipList(int val, const string& coinToss, SkipList* list) {
    int level = GetLevelFromCoinToss(coinToss);
    level = min(level, list->maxLevel); // 限制層數不超過最大層數

    vector<SkipListNode*> update(list->maxLevel, nullptr);
    SkipListNode* curr = list->head;

    // 找到每層的插入位置
    for (int i = list->maxLevel - 1; i >= 0; i--) {
        while (curr->forward[i] && curr->forward[i]->val < val) {
            curr = curr->forward[i];
        }
        update[i] = curr;
    }

    // 建立新節點
    SkipListNode* newNode = new SkipListNode(val, level);

    // 更新指針
    for (int i = 0; i < level; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

// 列印 SkipList
void PrintSkipList(SkipList* list) {
    cout << "SkipList:" << endl;
    for (int i = list->maxLevel - 1; i >= 0; i--) {
        SkipListNode* curr = list->head->forward[i];
        cout << "Level " << i + 1 << ": ";
        while (curr) {
            cout << curr->val << " ";
            curr = curr->forward[i];
        }
        cout << endl;
    }
}

// 計算 SkipList 的高度
int HeightSkipList(SkipList* list) {
    int height = 0;
    SkipListNode* curr = list->head;
    while (curr->forward[height]) {
        height++;
    }
    return height;
}

int main() {
    int maxLevel = 5; // 假設最大層數為 5
    SkipList* list = CreateSkipList(maxLevel);

    // 依序插入節點 (值, 銅板結果)
    InsertSkipList(1, "HHT", list);
    InsertSkipList(2, "T", list);
    InsertSkipList(3, "HT", list);
    InsertSkipList(4, "HHHT", list);
    InsertSkipList(5, "T", list);
    InsertSkipList(6, "T", list);
    InsertSkipList(7, "HHT", list);

    // 列印 SkipList
    PrintSkipList(list);

    // 列印高度
    cout << "SkipList 的最大高度：" << HeightSkipList(list) << endl;

    return 0;
}
