#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr), height(1) {}
};

// 取得節點高度
int GetHeight(TreeNode* node) {
     return node ? node->height : 0;
}

// 更新節點高度
void UpdateHeight(TreeNode* node) {
    if (node) {
        node->height = 1 + max(GetHeight(node->left), GetHeight(node->right));
    }
}

// 計算平衡因子
int GetBalance(TreeNode* node) {
    return node ? GetHeight(node->left) - GetHeight(node->right) : 0;
}

// 右旋操作
TreeNode* RightRotate(TreeNode* y) {
    TreeNode* x = y->left;
    TreeNode* T2 = x->right;

    // 旋轉
    x->right = y;
    y->left = T2;

    // 更新高度
    UpdateHeight(y);
    UpdateHeight(x);

    return x;
}

// 左旋操作
TreeNode* LeftRotate(TreeNode* x) {
    TreeNode* y = x->right;
    TreeNode* T2 = y->left;

    // 旋轉
    y->left = x;
    x->right = T2;

    // 更新高度
    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

// 建立僅包含一個數字的 AVL Tree
TreeNode* CreateAVL(int num) {
    return new TreeNode(num);
}

// 插入節點並保持 AVL 平衡
TreeNode* InsertAVL(int num, TreeNode* root) {
    if (root == nullptr) {
        return new TreeNode(num); // 新節點
    }

    // 遞迴插入節點
    if (num < root->val) {
        root->left = InsertAVL(num, root->left);
    } else if (num > root->val) {
        root->right = InsertAVL(num, root->right);
    } else {
        return root; // 不允許重複節點
    }

    // 更新高度
    UpdateHeight(root);

    // 檢查平衡因子
    int balance = GetBalance(root);

    // 左重：右旋
    if (balance > 1 && num < root->left->val) {
        return RightRotate(root);
    }

    // 右重：左旋
    if (balance < -1 && num > root->right->val) {
        return LeftRotate(root);
    }

    // 左右重：左旋後右旋
    if (balance > 1 && num > root->left->val) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // 右左重：右旋後左旋
    if (balance < -1 && num < root->right->val) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}

// 印出 AVL Tree (in-order)
void PrintAVL(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    PrintAVL(root->left);
    cout << root->val << " ";
    PrintAVL(root->right);
}

// 計算 AVL Tree 的高度
int HeightAVL(TreeNode* root) {
    return GetHeight(root);
}

int main() {
    TreeNode* root = nullptr;

    root = InsertAVL(1, root);
    root = InsertAVL(2, root);
    root = InsertAVL(3, root);
    root = InsertAVL(4, root);
    root = InsertAVL(5, root);
    root = InsertAVL(6, root);
    root = InsertAVL(7, root);

    cout << "AVL Tree 中的所有節點：" << endl;
    PrintAVL(root);
    cout << endl;

    cout << "AVL Tree 的高度：" << HeightAVL(root) << endl;

    return 0;
}
