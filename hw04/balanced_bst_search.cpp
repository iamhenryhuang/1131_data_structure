#include <iostream>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;

const int SEARCH_COUNT = 100000;  // 搜尋次數為十萬次

random_device rd;
mt19937 gen(rd());

double test_search(int k) {
    int n = 1 << k;
    uniform_int_distribution<int64_t> dis(1, (1LL << 30));
    
    // 準備插入的數據
    vector<int> numbers(n);
    for(int i = 0; i < n; i++) {
        numbers[i] = dis(gen);
    }
    
    // 建立 BST
    map<int, int> bst;
    for(int i = 0; i < n; i++) {
        bst[numbers[i]] = i;
    }
    
    // 準備搜尋的數據
    vector<int> search_numbers(SEARCH_COUNT);
    for(int i = 0; i < SEARCH_COUNT; i++) {
        search_numbers[i] = dis(gen);
    }
    
    // 進行搜尋並計時
    auto start = chrono::high_resolution_clock::now();
    
    int found_count = 0;
    for(int i = 0; i < SEARCH_COUNT; i++) {
        if(bst.find(search_numbers[i]) != bst.end()) {
            found_count++;
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double>(end - start).count();
    
    // 輸出找到的數量，用於驗證
    cout << "Found: " << found_count << " items" << endl;
    
    return time;
}

int main() {
    cout << fixed << setprecision(6);
    cout << "k\tn\t\tSearch Time(s)" << endl;
    cout << string(50, '-') << endl;
    
    for(int k = 10; k <= 30; k++) {
        double time = test_search(k);
        cout << k << "\t" 
             << (1 << k) << "\t\t"
             << time << endl;
    }
    
    return 0;
}
