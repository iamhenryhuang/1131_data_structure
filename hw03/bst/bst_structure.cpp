#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 生成僅包含該數字的bst，並返回其root
TreeNode* CreateBST(int num) {
    return new TreeNode(num);
}

// 將數字插入bst，返回更新後的 root
TreeNode* InsertBST(int num, TreeNode* root) {
    if (root == nullptr) {
        return new TreeNode(num); // 如果 root 為空，生成新節點
    }
    if (num < root->val) {
        root->left = InsertBST(num, root->left); // 插入到左子樹
    } else if (num > root->val) {
        root->right = InsertBST(num, root->right); // 插入到右子樹
    }
    return root; // 返回更新後的根節點
}

// 列印bst的所有節點
void PrintBST(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    PrintBST(root->left);               // in-order左子樹
    cout << root->val << " ";
    PrintBST(root->right);              // in-order右子樹
}

// 計算bst的高度
int HeightBST(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = HeightBST(root->left);
    int rightHeight = HeightBST(root->right);
    return max(leftHeight, rightHeight) +1; // 返回左右子樹高度的最大值+1
}

int main() {
    TreeNode* root = CreateBST(3);     // 建立根節點
    root = InsertBST(2, root);          // 插入數字
    root = InsertBST(1, root);
    root = InsertBST(5, root);
    root = InsertBST(4, root);

    cout << "BST 中的所有節點：" << endl;
    PrintBST(root);
    cout << endl;

    cout << "BST 的高度：" << HeightBST(root) << endl;

    return 0;
}
