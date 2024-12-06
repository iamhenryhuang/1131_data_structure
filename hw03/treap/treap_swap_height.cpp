#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>

using namespace std;

// 節點結構
struct TreapNode {
    int key; // 鍵值
    int priority; // 優先級
    TreapNode* left;
    TreapNode* right;
    TreapNode(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

// 計算 Treap 的高度
int getHeight(TreapNode* root) {
    if (!root) return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

// 右旋
TreapNode* rotateRight(TreapNode* y) {
    TreapNode* x = y->left;
    TreapNode* T = x->right;

    x->right = y;
    y->left = T;

    return x;
}

// 左旋
TreapNode* rotateLeft(TreapNode* x) {
    TreapNode* y = x->right;
    TreapNode* T = y->left;

    y->left = x;
    x->right = T;

    return y;
}

// 插入節點到 Treap
TreapNode* insert(TreapNode* root, int key) {
    if (!root) return new TreapNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
        if (root->left->priority > root->priority) {
            root = rotateRight(root);
        }
    } else if (key > root->key) {
        root->right = insert(root->right, key);
        if (root->right->priority > root->priority) {
            root = rotateLeft(root);
        }
    }

    return root;
}

// 清除樹的記憶體
void deleteTree(TreapNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    const int n = 1 << 20; // 2^20
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;

    mt19937 rng(random_device{}()); // 隨機生成器
    vector<double> avgHeights(21, 0.0); // 儲存每個 k 的平均高度

    for (int exp = 0; exp <= 20; ++exp) {
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

            TreapNode* root = nullptr;

            // 插入元素到 Treap
            for (int val : tempArr) {
                root = insert(root, val);
            }

            // 計算 Treap 的高度
            totalHeight += getHeight(root);

            deleteTree(root); // 清除樹的記憶體
        }

        avgHeights[exp] = totalHeight / 10; // 計算平均高度
        cout << "k = 2^" << exp << ", Average Height = " << avgHeights[exp] << endl;
    }

    return 0;
}
