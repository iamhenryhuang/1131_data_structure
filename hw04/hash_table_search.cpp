#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>
using namespace std;

const int SEARCH_COUNT = 100000;

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
    
    // 建立 hash table 並記錄其狀態
    unordered_map<int, int> hash_table;
    
    // 設置足夠大的 bucket 數來減少 rehash
    hash_table.reserve(n);
    
    for(int i = 0; i < n; i++) {
        hash_table[numbers[i]] = i;
    }
    
    // 準備搜尋的數據
    vector<int> search_numbers(SEARCH_COUNT);
    for(int i = 0; i < SEARCH_COUNT; i++) {
        search_numbers[i] = dis(gen);
    }
    
    // 輸出 hash table 的狀態
    cout << "Bucket count: " << hash_table.bucket_count() << endl;
    cout << "Load factor: " << hash_table.load_factor() << endl;
    cout << "Max load factor: " << hash_table.max_load_factor() << endl;
    
    // 進行搜尋並計時
    auto start = chrono::high_resolution_clock::now();
    
    int found_count = 0;
    for(int i = 0; i < SEARCH_COUNT; i++) {
        if(hash_table.find(search_numbers[i]) != hash_table.end()) {
            found_count++;
        }
    }
    
    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double>(end - start).count();
    
    cout << "Found: " << found_count << " items" << endl;
    
    return time;
}

int main() {
    cout << fixed << setprecision(6);
    cout << "k\tn\t\tSearch Time(s)" << endl;
    cout << string(50, '-') << endl;
    
    for(int k = 10; k <= 30; k++) {
        cout << "\nTesting k = " << k << ":" << endl;
        double time = test_search(k);
        cout << k << "\t" 
             << (1 << k) << "\t\t"
             << time << endl;
    }
    
    return 0;
}
