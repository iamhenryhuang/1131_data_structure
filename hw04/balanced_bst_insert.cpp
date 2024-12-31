#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;

// 用於生成隨機數的函數
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int64_t> dis(1, (1LL << 30));

// 測試特定大小的插入操作
double test_insertion(int k) {
    int n = 1 << k;  // n = 2^k
    
    // 準備隨機數據
    vector<int> numbers(n);
    for(int i = 0; i < n; i++) {
        numbers[i] = dis(gen);
    }
    
    // 測試 map (BST)
    map<int, int> bst;
    auto start = chrono::high_resolution_clock::now();
    
    for(int i = 0; i < n; i++) {
        bst[numbers[i]] = i;
    }
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double>(end - start).count();
}

int main() {
    cout << fixed << setprecision(6);
    cout << "k\tn\t\tBST(s)" << endl;
    cout << string(40, '-') << endl;
    
    for(int k = 10; k <= 30; k++) {
        double time = test_insertion(k);
        cout << k << "\t" 
             << (1 << k) << "\t\t"
             << time << endl;
    }
    
    return 0;
}
