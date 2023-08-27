template<int lg>
struct sparse_table{
    int n;
    using T = int;
    vector<array<T, lg>> st;
    T base = 0;

    inline T join(T x, T y){
        return min(x, y);
    }

    sparse_table (vector<T> a){
        n = a.size();
        st.resize(n);

        for (int i = 0; i < n; i++){
            st[i][0] = a[i];
        }

        for (int i = 1; i < lg; i++){
            int v = (1<<(i-1));
            for (int j = 0; j < n; j++){
                st[j][i] = join(st[j][i-1], st[min(n-1, j+v)][i-1]);
            }
        }
    }

    inline T get1(int l, int r){
        int s = r-l+1; 
        int v = __builtin_clz(s);

        return join(st[l][v], st[r-(1<<v)+1][v]);
    }


    inline T get2(int l, int r){
        int s = r-l+1;
        int a = base; 
        T val = base;

        for(int i = lg-1; i >= 0; i--){
            if((1<<i) >= s){
                val = join(val, st[l][i]);
                l+=(1<<i);
            }
        }

        return val;
    }

};
