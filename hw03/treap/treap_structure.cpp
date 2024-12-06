#include <iostream>
using namespace std;

// 節點結構
struct TreeNode {
    int val;        // 節點value
    double priority; // 節點priority (min-heap)
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x, double p) : val(x), priority(p), left(nullptr), right(nullptr) {}
};

// 右旋操作
TreeNode* RightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // 執行旋轉
    x->right = y;
    y->left = T2;

    return x;
}

// 左旋操作
TreeNode* LeftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // 執行旋轉
    y->left = x;
    x->right = T2;

    return y;
}

// 建立僅包含一個數字的 Treap 節點
TreeNode* CreateTreap(int num, double priority) {
    return new TreeNode(num, priority);
}

// 維持 BST 和 min-heap 性質
TreeNode* InsertTreap(int num, double priority, TreeNode* root) {
    if (root == nullptr) {
        return CreateTreap(num, priority); // 建立新節點
    }

    // 按 BST 性質插入節點
    if (num < root->val) {
        root->left = InsertTreap(num, priority, root->left);

        // 維持 min-heap 性質
        if (root->left->priority < root->priority) {
            root = RightRotate(root);
        }
    } else if (num > root->val) {
        root->right = InsertTreap(num, priority, root->right);

        // 維持 min-heap 性質
        if (root->right->priority < root->priority) {
            root = LeftRotate(root);
        }
    }

    return root;
}

// 列印 Treap (in-order)
void PrintTreap(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    PrintTreap(root->left);
    cout << "(" << root->val << ", " << root->priority << ") ";
    PrintTreap(root->right);
}

// 計算 Treap 的高度
int HeightTreap(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = HeightTreap(root->left);
    int rightHeight = HeightTreap(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    TreeNode* root = nullptr;

    // 依序插入節點 (value, priority)
    root = InsertTreap(3, 0.9, root);
    root = InsertTreap(2, 0.5, root);
    root = InsertTreap(1, 0.3, root);
    root = InsertTreap(5, 0.2, root);
    root = InsertTreap(4, 0.1, root);

    cout << "Treap 中的所有節點：" << endl;
    PrintTreap(root);
    cout << endl;

    cout << "Treap 的高度：" << HeightTreap(root) << endl;

    return 0;
}
