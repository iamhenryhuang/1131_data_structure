#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <cmath>

using namespace std;
using namespace chrono;

// 節點結構
struct TreeNode {
    int val;
    int height; // 節點高度
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}
};

// 獲取節點高度
int getHeight(TreeNode* node) {
    return node ? node->height : 0;
}

// 更新節點高度
void updateHeight(TreeNode* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

// 計算平衡因子
int getBalance(TreeNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// 左旋
TreeNode* rotateLeft(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// 右旋
TreeNode* rotateRight(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// 插入節點並平衡
TreeNode* insert(TreeNode* node, int val) {
    if (!node) return new TreeNode(val);

    if (val < node->val) {
        node->left = insert(node->left, val);
    } else if (val > node->val) {
        node->right = insert(node->right, val);
    } else {
        return node; // 重複值不插入
    }

    updateHeight(node);

    int balance = getBalance(node);

    // 左左情況
    if (balance > 1 && val < node->left->val) {
        return rotateRight(node);
    }

    // 右右情況
    if (balance < -1 && val > node->right->val) {
        return rotateLeft(node);
    }

    // 左右情況
    if (balance > 1 && val > node->left->val) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // 右左情況
    if (balance < -1 && val < node->right->val) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// 清除樹的記憶體
void deleteTree(TreeNode* root) {
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
    vector<double> avgTimes(21, 0.0); // 儲存每個 k 的平均時間

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

            TreeNode* root = nullptr;
            auto start = high_resolution_clock::now(); // 開始計時

            // 插入元素到 AVL Tree
            for (int val : tempArr) {
                root = insert(root, val);
            }

            auto end = high_resolution_clock::now(); // 結束計時
            totalTime += duration_cast<nanoseconds>(end - start).count() / 1e9; // 秒為單位

            deleteTree(root); // 清除樹的記憶體
        }

        avgTimes[exp] = totalTime / 10; // 計算平均時間
        cout << "k = 2^" << exp << ", Average Time = " << avgTimes[exp] << " seconds" << endl;
    }

    return 0;
}
