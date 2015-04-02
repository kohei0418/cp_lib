#include <vector>

using namespace std;

template <typename T>
struct CombTable {
    int size_;
    vector<vector<T>> table_;
    T mod_;

    CombTable(int size, T mod = -1) {
        size_ = size + 1;
        mod_ = mod;
        table_.resize(size_);
        for(int i = 0; i < size_; i++) 
            table_[i].resize(size_);
        for(int i = 1; i < size_; i++) {
            for(int j = 0; j <= i; j++) {
                if(j == 0) table_[i][j] = 1;
                else if(j == 1) table_[i][j] = i;
                else if(i == j) table_[i][j] = 1;
                else table_[i][j] = 0;
            }
        }
    }
    
    T get(int n, int m) {
        if(table_[n][m] > 0) return table_[n][m];
        else {
            table_[n][m] = get(n-1, m) + get(n-1, m-1);
            if(mod_ > 0) return table_[n][m] %= mod_;
            else return table_[n][m];
        }
    }
};


// verify
#include <cstdlib>
#include <cassert>
#include <iostream>

long long comb(int n, int m) {
    if(m == 0 || n == m) return 1LL;
    else if(m == 1) return (long long)n;
    else return comb(n-1, m) + comb(n-1, m-1);
}

int main() {
    int size;
    cout << "size: ";
    cin >> size;
    int mod;
    cout << "mod: ";
    cin >> mod;

    CombTable<long long> table(size, mod);
    int n, m;  

    while(true) {
        cin >> n >> m;
        if(n == 0 && m == 0) break;

        long long res = table.get(n, m);

        cerr << n << "C" << m << " = " << res << endl;
    }

    return 0;
}
