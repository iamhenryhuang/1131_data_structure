#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;

// 節點結構
struct BSTNode {
    int key; // 節點鍵值
    BSTNode* left;
    BSTNode* right;
    BSTNode(int k) : key(k), left(nullptr), right(nullptr) {}
};

// 插入節點到 Binary Search Tree
BSTNode* insert(BSTNode* root, int key) {
    if (!root) return new BSTNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    return root; // 重複值不插入
}

// 清除樹的記憶體
void deleteTree(BSTNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// 計算二元搜尋樹的高度
int calculateHeight(BSTNode* root) {
    if (!root) return 0;
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    const int n = 1 << 20; // 2^20
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;

    mt19937 rng(random_device{}()); // 隨機生成器
    vector<double> avgHeights(21, 0.0); // 儲存每個 k 的平均高度

    for (int exp = 20; exp >= 0; exp--) {
        int k = 1 << exp; // 2^exp
        double totalHeight = 0.0;

        for (int t = 0; t < 10; ++t) { // 進行 10 次測試
            vector<int> tempArr = arr;

            // 隨機交換 k 次
            for (int i = 0; i < k; ++i) {
                int idx1 = rng() % n;
                int idx2 = rng() % n;
                swap(tempArr[idx1], tempArr[idx2]);
            }

            BSTNode* root = nullptr;

            // 插入元素到 Binary Search Tree
            for (int val : tempArr) {
                root = insert(root, val);
            }

            // 計算樹的高度
            int height = calculateHeight(root);
            totalHeight += height;

            deleteTree(root); // 清除樹的記憶體
        }

        avgHeights[exp] = totalHeight / 10; // 計算平均高度
        cout << "k = 2^" << exp << ", Average Height = " << avgHeights[exp] << endl;
    }

    return 0;
}
