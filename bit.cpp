#include <vector>

using namespace std;


struct BIT {
    int n_;
    vector<int> bit_;

    BIT(int n)
    : n_(n)
    {
        bit_.assign(n_ + 1, 0);
    }

    int sum(int i) {
        int s = 0;
        while(i > 0) {
            s += bit_[i];
            i -= i & -i;
        }
        return s;
    }

    void add(int i, int x) {
        while(i <= n_) {
            bit_[i] += x;
            i += i & -i;
        }
    }
};
