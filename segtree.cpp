struct Segtree {                                                
        int n;      
        using T = int;

        T join(const T& x, const T& y){
            return x+y;
        }

        T base = 0;
        vector<T> arr;                                        
        Segtree(int n) : n(n), arr(2*n, base) {}                  
        
        void update(int i, int x) {                             
                for (arr[i += n] = x; i > 1; i >>= 1)           
                        arr[i>>1] = join(arr[i], arr[i^1]);      
        }                                                       
        T operator()(int l, int r) {                               
                T accl = base;
                T accr = base;                        
                for (l += n, r += n+1; l != r; l >>= 1, r >>= 1) {
                        if (l&1) accl = join(accl, arr[l++]);      
                        if (r&1) accr = join(arr[--r], accr);      
                }                                               
                return join(accl, accr);                                     
        }                                                       
};  
