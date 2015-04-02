#include <vector>

using namespace std;

template <typename T>
struct CombTable {
    T **table;
    int size;
    T mod;
    CombTable(int size_, T mod_ = -1) {
        size = size_ + 1;
        mod = mod_;
        table = new T*[size];
        for(int i = 0; i < size; i++) 
            table[i] = new T[size];
        for(int i = 1; i < size; i++) {
            for(int j = 0; j <= i; j++) {
                if(j == 0) table[i][j] = 1;
                else if(j == 1) table[i][j] = i;
                else if(i == j) table[i][j] = 1;
                else table[i][j] = 0;
            }
        }
    }
    ~CombTable() {
        for(int i = 0; i < size; i++) delete[] table[i];
        delete[] table;
    }

    T get(int n, int m) {
        if(table[n][m] > 0) return table[n][m];
        else {
            table[n][m] = get(n-1, m) + get(n-1, m-1);
            if(mod > 0) return table[n][m] %= mod;
            else return table[n][m];
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
