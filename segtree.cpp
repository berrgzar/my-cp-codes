struct Segtree{
    int n;
    using T = int;
 
    T base = 0;
    vector<T> arr;
 
    T merge(const int &x, const int &y){
        return (x+y);
    }
 
    Segtree(int n) : n(n), arr(2*n, base) {}
 
    void update(int i, T x){
        for (arr[i += n] += x; i > 1; i >>=1){
            i >>= 1;
            arr[i] = merge(arr[i<<1], arr[(i<<1) ^ 1]);
            i <<= 1;
        }
    }
 
    T operator()(int l, int r){
        T accl = base;
        T accr = base;
 
        for (l+=n, r+=n+1; l != r; l>>=1, r>>=1){
            if (l&1) accl = merge(accl, arr[l++]);
            if (r&1) accr = merge (arr[--r], accr);
        }
 
        return merge(accl, accr);
    }


}; 
