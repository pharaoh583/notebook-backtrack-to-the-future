inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
    if (pow == 0) return 0;
    int hpow = 1 << (pow-1);
    int seg = (x < hpow) 
            ? ((y < hpow) ? 0 : 3) 
            : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2*pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow-1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}
const int bs = 450;
struct Query {
    int l, r, idx;
    int64_t ord;
    inline void calcOrder() {
        ord = hilbertOrder(l, r, 21, 0);
    }
    bool operator <(query &other) const {
        return ord < other.ord;
    }
    static bool cmp(pair<int, int> p, pair<int, int> q) {
        if (p.first / bs != q.first / bs)
            return p < q;
        return (p.first / bs & 1) ? (p.second < q.second) : (p.second > q.second);
    }
};
//TODO: implement add function add(idx)
//TODO: implement remove function remove(idx)
//TODO: find way to get answer
vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
    sort(all(queries);
    // TODO: initialize data structure
    int cur_l = 0;
    int cur_r = -1;
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}
