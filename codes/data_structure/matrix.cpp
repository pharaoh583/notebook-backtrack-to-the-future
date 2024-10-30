class Matrix{
public:
    int r, c;
    vector<vi> m;
    Matrix(int rows, int cols) : r(rows), c(cols){
        m = vector<vi>(r, vi(c, 0));
    }
    Matrix(int n) : Matrix(n, n){
        forn(i, r) m[i][i] = 1; 
    }
    Matrix(vector<vi> mt) : Matrix(mt.size(), mt[0].size()) {
        m = mt;
    }
    Matrix operator * (Matrix b) {
        Matrix res(r, b.c);
        forn(i, r) {
            forn(j, b.c) {
                forn(k, c) {
                    res.m[i][j] = (res.m[i][j] + (m[i][k] * b.m[k][j])%M)%M;
                }
            }
        }
        return res;
    }
