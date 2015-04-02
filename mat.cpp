#include <vector>

using namespace std;


class VectorM {
private:
    vector<int> data;
    int vsize;
    int M;
public:
    VectorM() { vsize = 0; M = 0; }
    VectorM(int _vsize, int _M) { 
        data.assign(_vsize, 0); vsize = _vsize; M = _M;
    }
    int size() const { return vsize; }
    void clear() { data.clear(); }
    void resize(int _vsize) { data.resize(_vsize); vsize = _vsize; } 
    int mod() const { return M; }
    int mod(int _M) { M = _M; return M; }
    const int &operator[](const int idx) const { return data[idx]; }
    int &operator[](const int idx) { return data[idx]; }
    VectorM operator*(const int mul) const {
        VectorM res(vsize, M);
        for(int i = 0; i < vsize; i++) res[i] = (ll)data[i] * mul % M;
        return res;
    }
};
VectorM operator*(const int mul, const VectorM &v) {
    VectorM res(v.size(), v.mod());
    for(int i = 0; i < (int)v.size(); i++) res[i] = (ll)v[i] * mul % v.mod();
    return res;
}

class MatrixM {
private:
    vector<VectorM> data;
    int rows, cols;
    int M;
public:
    MatrixM() { rows = 0; cols = 0; M = 0; }
    MatrixM(int _rows, int _M) {
        rows = _rows; cols = _rows; M = _M;
        data.assign(rows, VectorM(rows, M));
        for(int i = 0; i < rows; i++) data[i][i] = 1;
    }
    MatrixM(int _rows, int _cols, int _M) {
        rows = _rows; cols = _cols; M = _M;
        data.assign(rows, VectorM(cols, M));
    }
    int rowsize() const { return rows; };
    int colsize() const { return cols; };
    void clear() { data.clear(); }
    void resize(int _rows, int _cols) {
        rows = _rows; cols = _cols;
        data.resize(rows);
        for(int i = 0; i < rows; i++) data[i].resize(cols);
    }
    int mod() const { return M; }
    int mod(int _M) { M = _M; return M; }
    const VectorM &operator[](const int idx) const { return data[idx]; }
    VectorM &operator[](const int idx) { return data[idx]; }

    MatrixM operator*(const int mul) const {
        MatrixM res(rows, cols, M);
        for(int i = 0; i < rows; i++) 
            for(int j = 0; j < cols; j++)
                res[i][j] = ((ll)data[i][j] * mul) % M;
        return res;
    }
    MatrixM operator*(const MatrixM b) const {
        if(cols!= (int)b.rowsize()) return MatrixM(0, 0, M);
        MatrixM res(rows, b.colsize(), M);
        for(int i = 0; i < rows; i++) for(int j = 0; j < cols; j++) {
            ll tmp = 0;
            for(int k = 0; k < cols; k++) tmp += (ll)data[i][k] * b[k][j] % M;
                res[i][j] = (int)(tmp % M);
        }
        return res;
    }
    VectorM operator*(const VectorM v) const {
        if(cols != (int)v.size()) return VectorM(0, M);
        VectorM res(rows, M);
        for(int i = 0; i < rows; i++) {
            ll tmp = 0;
            for(int j = 0; j < cols; j++) tmp += (ll)data[i][j] * v[j] % M;
                res[i] = (int)(tmp % M);
        }
        return res;
    }
    MatrixM pow(ll n) {
        if(rows != cols) return MatrixM(0, 0, M);
        else if(n == 0) return MatrixM(rows, M);
        else if(n % 2 == 0) {
            MatrixM tmp = this->pow(n/2);
            return tmp * tmp;
        }
        else {
            return (*this) * (this->pow(n-1));
        }
    }
};

MatrixM operator*(const int mul, const MatrixM &m) {
    MatrixM res(m.rowsize(), m.colsize(), m.mod());
    for(int i = 0; i < (int)m.rowsize(); i++) 
        for(int j = 0; j < (int)m.colsize(); j++) {
            res[i][j] = (ll)m[i][j] * mul % m.mod();
        }
    return res;
}   
